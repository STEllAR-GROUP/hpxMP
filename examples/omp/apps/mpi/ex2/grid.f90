MODULE Grid
  ! Configuration
  INTEGER :: nprocs           ! The number of processes
  INTEGER :: myrank           ! The rank of this process among the processes
  INTEGER :: rows             ! The number of element rows 
  INTEGER :: cols             ! The number of element columns
  INTEGER :: localCols        ! The number of columns per process

  ! The element and node grids
  REAL(KIND=8), DIMENSION(:,:), ALLOCATABLE :: elements
  REAL(KIND=8), DIMENSION(:,:), ALLOCATABLE :: nodes

CONTAINS

  SUBROUTINE initialize()
    IMPLICIT NONE
    INCLUDE 'mpif.h'

    INTEGER :: status

    ! Get the size of the inner element grid
    call getGridSize(rows, cols, status)
    IF (status /= 0) STOP

    ! Initialize MPI
    CALL MPI_INIT(status)
    CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, status)
    CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, status)

    ! Ensure that the number of columns is divisible by the number of processes
    IF (MOD(cols, nprocs) /= 0) THEN
      IF (myrank == 0) THEN
        WRITE (*,*) "Error: the number of element columns must be divisible by the number of processes."
      ENDIF

      CALL MPI_FINALIZE(status)
      STOP
    ENDIF

    localCols = cols / nprocs

    ! Allocate the element grid and the node grid

    ! There is 1 extra column at the end for receiving elements 
    ! from the process with rank myrank+1.
    ALLOCATE(elements(rows, localCols+1))

    ! The nodes "surround" the elements, so the must be 1 node column more 
    ! than the element columns (not counting the extra buffer column)
    ! Process 0 owns all of the nodes, but for process 1... the left-most
    ! node column is for receiving nodes from the process with rank myrank-1
    ALLOCATE(nodes(rows+1, localCols+1))
  END SUBROUTINE initialize

  ! ***************************************************************************

  SUBROUTINE getGridSize(rows, cols, status)
    IMPLICIT NONE

    INTEGER, INTENT(OUT) :: rows   ! The number of element rows
    INTEGER, INTENT(OUT) :: cols   ! The number of element columns
    INTEGER, INTENT(OUT) :: status ! 0 if everything is OK, otherwise /= 0

    INTEGER*4            :: iargc  ! Function, number of command line arguments
    INTEGER              :: nargs  ! The number of command line arguments
    CHARACTER(LEN=128)   :: arg    ! A command line argument

    status = 0

    ! Get the number of rows and columns from the command line
    nargs = iargc();
    IF (nargs == 2) THEN
      ! Rows
      CALL getarg(1, arg)
      READ (arg, *, IOSTAT=status) rows

      IF (status /= 0) THEN
        WRITE (*,*) "Error: please specify the number of rows as the first argument"
      ELSE   ! Columns
        CALL getarg(2, arg)
        READ (arg, *, IOSTAT=status) cols
        IF (status /= 0) THEN
          WRITE (*,*) "Error: please specify the number of columns as the second argument"
        ENDIF
      ENDIF
    ELSE 
      WRITE (*,*) "Error: please specify the number of rows and columns as arguments"
      status = 1
    ENDIF
  END SUBROUTINE getGridSize

  ! ***************************************************************************

  SUBROUTINE synchronizeElements()
    IMPLICIT NONE
    INCLUDE 'mpif.h'

    INTEGER :: status(MPI_STATUS_SIZE)    ! The MPI statuses
    INTEGER :: ierr

    ! Send the left-most elements to process myrank-1 and 
    ! receive the right-most elements from process myrank+1

    ! Send the left-most element column to the process with the rank myrank-1
    IF (myrank > 0) THEN
      CALL MPI_Send(elements(1,1), rows, MPI_REAL8, myrank-1, 1, &
                    MPI_COMM_WORLD, ierr)
    ENDIF

    ! Receive the right-most element column from the process with the rank 
    ! myrank+1
    IF (myrank < nprocs-1) THEN
      CALL MPI_Recv(elements(1,localCols+1), rows, MPI_REAL8, myrank+1, 1, &
                    MPI_COMM_WORLD, status, ierr)
    ENDIF
  END SUBROUTINE synchronizeElements

  ! ***************************************************************************

  SUBROUTINE synchronizeNodes()
    IMPLICIT NONE
    INCLUDE 'mpif.h'

    INTEGER :: status(MPI_STATUS_SIZE)    ! The MPI statuses
    INTEGER :: ierr

    ! Receive the left-most nodes from process myrank-1 and 
    ! send the right-most elements to process myrank+1

    ! Receive the left-most node column from the process with the rank myrank-1
    IF (myrank > 0) THEN
      CALL MPI_Recv(nodes(1,1), rows+1, MPI_REAL8, myrank-1, 2, &
                    MPI_COMM_WORLD, status, ierr)
    ENDIF

    ! Send the right-most node column to the process with the rank myrank+1
    IF (myrank < nprocs-1) THEN
      CALL MPI_Send(nodes(1,localCols+1), rows+1, MPI_REAL8, myrank+1, 2, &
                    MPI_COMM_WORLD, ierr)
    ENDIF
  END SUBROUTINE synchronizeNodes

  ! ***************************************************************************

  SUBROUTINE printGrids(msg)
    IMPLICIT NONE
    INCLUDE 'mpif.h'

    CHARACTER(len=*), INTENT(IN) :: msg

    REAL(KIND=8), DIMENSION(rows,cols) :: allElements
    REAL(KIND=8), DIMENSION(rows+1,cols+1) :: allNodes
    INTEGER :: ierr
    INTEGER :: r

    ! Gather the elements on the root process
    CALL MPI_Gather(elements(1,1), rows*localCols, MPI_REAL8, allElements, &
                     rows*localCols, MPI_REAL8, 0, MPI_COMM_WORLD, ierr)

    ! Copy the first column on the root process from nodes to allNodes
    IF (myrank == 0) THEN
      allNodes(:,1) = nodes(:,1)
    ENDIF

    ! Gather localCols columns of nodes from each process on allNodes
    CALL MPI_Gather(nodes(1,2), (rows+1)*localCols, MPI_REAL8, allNodes(1,2), &
                     (rows+1)*localCols, MPI_REAL8, 0, MPI_COMM_WORLD, ierr)

    IF (myrank == 0) THEN
      WRITE (*,*) msg, ':'
      DO r=1, rows
        WRITE (*,100) allNodes(r,:)
        WRITE (*,110) allElements(r,:)
      END DO
      WRITE (*,100) allNodes(rows+1,:)
      WRITE (*,*) ''
      100 FORMAT (1000(F8.2,1X))
      110 FORMAT (4X,1000(F8.2,1X))
    ENDIF
  END SUBROUTINE printGrids

  ! ***************************************************************************

  SUBROUTINE finalize()
    IMPLICIT NONE

    INTEGER :: status

    CALL MPI_Finalize(status)
  END SUBROUTINE finalize
END MODULE Grid
