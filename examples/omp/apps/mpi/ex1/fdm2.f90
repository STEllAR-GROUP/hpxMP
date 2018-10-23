PROGRAM FDM2
  ! This program demonstrates the parallelization of a program using the 
  ! 2D Finite Difference Method (FDM). In this example, row-wise 
  ! block-distribution is used and the boundary elements between processes
  ! are not contiguous in memory. One must therefore either use derived data
  ! types representing the boundary elements, or write code for packing data, 
  ! sending/receiving it, and unpacking it. In this example, the last 
  ! method is used.

  IMPLICIT NONE
  INCLUDE 'mpif.h'

  ! Configuration variables
  INTEGER, PARAMETER :: rows = 12
  INTEGER, PARAMETER :: cols = 9
  REAL(KIND=8), DIMENSION(rows,cols) :: a
  REAL(KIND=8), DIMENSION(rows,cols) :: b

  ! Send and receive buffers
  REAl(KIND=8), DIMENSION(cols) :: sndbuf1
  REAL(KIND=8), DIMENSION(cols) :: sndbuf2
  REAL(KIND=8), DIMENSION(cols) :: rcvbuf1
  REAL(KIND=8), DIMENSION(cols) :: rcvbuf2

  ! MPI variables
  INTEGER :: nprocs
  INTEGER :: myrank
  INTEGER, DIMENSION(4)                  :: requests
  INTEGER, DIMENSION(MPI_STATUS_SIZE, 4) :: statuses
  INTEGER :: ierr

  ! Count variables
  INTEGER :: i, j, count
  INTEGER :: ista, iend, ista2, iend2

  ! Initialize MPI
  CALL MPI_INIT(ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)

  ! Calculate the range (ista, iend) on which this process operates
  CALL para_range(1, rows, nprocs, myrank, ista, iend)

  ! Initialize the matrix a
  DO j = 1, cols
    DO i = ista, iend
      a(i,j) = i + 10.0 * j
    ENDDO
  ENDDO

  count = 0
  !  Data exchange with process myrank-1
  IF (myrank > 0) THEN
    ! Copy data from the matrix a to send buffer 1
    sndbuf1 = a(ista,:)
    
    ! Send data in send buffer 1 and receive data in receive buffer 1
    CALL MPI_ISEND(sndbuf1, cols, MPI_REAL8, myrank-1, 1, MPI_COMM_WORLD, &
                   requests(count+1), ierr)
    CALL MPI_IRECV(rcvbuf1, cols, MPI_REAL8, myrank-1, 1, MPI_COMM_WORLD, &
                   requests(count+2), ierr)
    count = count + 2
  ENDIF

  !  Data exchange with process myrank+1
  IF (myrank < nprocs-1) THEN
    ! Copy data from the matrix a to send buffer 2
    sndbuf2 = a(iend,:)

    CALL MPI_ISEND(sndbuf2, cols, MPI_REAL8, myrank+1, 1, MPI_COMM_WORLD, &
                   requests(count+1), ierr)
    CALL MPI_IRECV(rcvbuf2, cols, MPI_REAL8, myrank+1, 1, MPI_COMM_WORLD, &
                   requests(count+2), ierr)
    count = count + 2
  ENDIF

  ! Take process 0 and process nprocs-1 into account, when updating b
  ista2 = ista
  iend2 = iend
  IF (myrank == 0) ista2 = 2
  IF (myrank == nprocs - 1) iend2 = cols - 1

  ! Wait until all data exchanges have taken place
  CALL MPI_WAITALL(count, requests, statuses, ierr)

  ! Copy data back to a from the two receive buffers
  IF (myrank >  0)         a(ista-1,:) = rcvbuf1
  IF (myrank < nprocs - 1) a(iend+1,:) = rcvbuf2

  ! Update the matrix b
  DO j = 2, cols-1
    DO i = ista2, iend2
      b(i,j) = a(i-1,j) + a(i,j-1) + a(i,j+1) + a(i+1,j)
    ENDDO
  ENDDO

  ! Exit MPI
  CALL MPI_FINALIZE(ierr)
END

! A utility subroutine that calculates the range of iterations of
! a particular process. 
SUBROUTINE para_range(n1, n2, nprocs, irank, ista, iend)
  IMPLICIT NONE

  INTEGER, INTENT(IN)  :: n1     ! The min. value of the iteration variable
  INTEGER, INTENT(IN)  :: n2     ! The max. value of the iteration variable
  INTEGER, INTENT(IN)  :: nprocs ! The number of processes
  INTEGER, INTENT(IN)  :: irank  ! The rank for which you want to know the range
  INTEGER, INTENT(OUT) :: ista   ! The min. value of the range for process irank
  INTEGER, INTENT(OUT) :: iend   ! The max. value of the range for process irank

  INTEGER :: iwork1
  INTEGER :: iwork2

  iwork1 = (n2 - n1 + 1) / nprocs
  iwork2 = MOD(n2 - n1 + 1, nprocs)
  ista = irank * iwork1 + n1 + MIN(irank, iwork2)
  iend = ista + iwork1 - 1
  IF (iwork2 > irank) iend = iend + 1
END
