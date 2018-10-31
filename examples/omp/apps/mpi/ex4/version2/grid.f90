MODULE Grid
  ! Configuration
  INTEGER :: nprocs       ! The number of processes
  INTEGER :: myrank       ! The rank of this process among the processes
  INTEGER :: rows         ! The number of element rows 
  INTEGER :: cols         ! The number of element columns
  INTEGER :: localCols    ! The number of columns per process
  INTEGER :: odd          ! 1 if the global column number is odd for this 
                          ! process, 0 if it is even
  INTEGER :: even         ! 1 if the global column number is even for this 
                          ! process, 0 if it is odd
  INTEGER :: odd2         ! 1 if the global column number of the last column
                          ! is odd, 0 if it is even
  INTEGER :: even2        ! 1 if the global column number of the last column
                          ! is even, 0 if it is odd

  ! The grid
  REAL(KIND=8), DIMENSION(:,:), ALLOCATABLE :: x

CONTAINS

  SUBROUTINE initialize()
    IMPLICIT NONE
    INCLUDE 'mpif.h'

    ! MPI Variable
    INTEGER :: status

    ! Command line argument variables
    INTEGER*4          :: iargc  ! Function, number of command line arguments
    INTEGER            :: nargs  ! The number of command line arguments
    CHARACTER(LEN=128) :: arg    ! A command line argument

    ! Get the number of rows and columns from the command line
    nargs = iargc();
    IF (nargs == 2) THEN
      ! Rows
      CALL getarg(1, arg)
      READ (arg, *, IOSTAT=status) rows

      IF (status /= 0) THEN
        WRITE (*,*) "Error: please specify the number of rows as the first argument"
        STOP
      ELSE   ! Columns
        CALL getarg(2, arg)
        READ (arg, *, IOSTAT=status) cols
        IF (status /= 0) THEN
          WRITE (*,*) "Error: please specify the number of columns as the second argument"
          STOP
        ENDIF
      ENDIF
    ELSE 
      WRITE (*,*) "Error: please specify the number of rows and columns as arguments"
      STOP
    ENDIF

    ! Initialize MPI
    CALL MPI_INIT(status)
    CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, status)
    CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, status)

    ! Ensure that the number of columns is divisible by the number of processes
    IF (MOD(cols, nprocs) /= 0) THEN
      IF (myrank == 0) THEN
        WRITE (*,*) "Error: the number of columns must be divisible by the number of processes."
      ENDIF

      CALL MPI_FINALIZE(status)
      STOP
    ENDIF

    ! The number of columns managed by this process
    localCols = cols / nprocs

    ! Is the global column number for this process even?
    odd  = MOD((1+myrank*localCols), 2)
    even = 1-odd

    ! Is the global column number of the last column odd?
    odd2  = MOD((myrank+1)*localCols, 2)
    even2 = 1-odd2

    ! Ensure that there is a buffer space around the main area
    ALLOCATE(x(0:rows+1, 0:localCols+1))
  END SUBROUTINE initialize

  ! ***************************************************************************

  SUBROUTINE synchronize(iflg)
    IMPLICIT NONE
    INCLUDE 'mpif.h'

    INTEGER, INTENT(IN)   :: iflg

    ! MPI variables
    INTEGER, DIMENSION(2) :: requests
    INTEGER               :: statuses(MPI_STATUS_SIZE, 2)
    INTEGER               :: ierr
    INTEGER               :: count

    count = 0

    !  Data exchange with process myrank-1
    IF (myrank > 0) THEN
      count = count + 1
      IF (iflg == even) THEN
        CALL MPI_IRECV(x(1,0), rows,  MPI_REAL8, myrank-1, 1, &
                       MPI_COMM_WORLD, requests(count), ierr)
      ELSE
        CALL MPI_ISEND(x(1,1), rows, MPI_REAL8, myrank-1, 1, &
                       MPI_COMM_WORLD, requests(count), ierr)
      ENDIF
    ENDIF

    !  Data exchange with process myrank+1
    IF (myrank < nprocs - 1) THEN
      count = count + 1
      IF (iflg == even2) THEN
        CALL MPI_IRECV(x(1,localCols+1), rows,  MPI_REAL8, myrank+1, 1, &
                       MPI_COMM_WORLD, requests(count), ierr)
      ELSE
        CALL MPI_ISEND(x(1,localCols), rows, MPI_REAL8, myrank+1, 1, &
                       MPI_COMM_WORLD, requests(count), ierr)
      ENDIF
    ENDIF
    
    ! Wait until all data exchanges have taken place
    CALL MPI_WAITALL(count, requests, statuses, ierr)
  END SUBROUTINE synchronize

  ! ***************************************************************************

  SUBROUTINE printGrid(msg)
    IMPLICIT NONE
    INCLUDE 'mpif.h'

    CHARACTER(len=*), INTENT(IN) :: msg

    REAL(KIND=8), DIMENSION(0:rows+1,cols) :: globalX
    INTEGER :: ierr
    INTEGER :: r

    ! Gather the elements on the root process
    CALL MPI_Gather(x(0,1), (rows+2)*localCols, MPI_REAL8, globalX, &
                     (rows+2)*localCols, MPI_REAL8, 0, MPI_COMM_WORLD, ierr)

    IF (myrank == 0) THEN
      WRITE (*,*) msg, ':'
      WRITE (*,100) globalX(0,:)
      WRITE (*,*) ''
      DO r=1, rows
        WRITE (*,100) globalX(r,:)
      END DO
      WRITE (*,*) ''
      WRITE (*,100) globalX(rows+1,:)
      WRITE (*,*) ''
      100 FORMAT (1000(F7.2,1X))
    ENDIF
  END SUBROUTINE printGrid

  ! ***************************************************************************

  SUBROUTINE finalize()
    IMPLICIT NONE

    INTEGER :: status

    ! Clean up
    DEALLOCATE(x)

    CALL MPI_Finalize(status)
  END SUBROUTINE finalize

END MODULE Grid
