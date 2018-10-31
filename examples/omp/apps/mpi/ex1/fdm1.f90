PROGRAM FDM1
  ! This program demonstrates the parallelization of a program using the 
  ! 2D Finite Difference Method (FDM). In this example, column-wise 
  ! block-distribution is used and the boundary elements between processes
  ! are therefore contiguous in memory.

  IMPLICIT NONE
  INCLUDE 'mpif.h'

  ! Configuration variables
  INTEGER, PARAMETER :: rows = 6
  INTEGER, PARAMETER :: cols = 9
  REAL(KIND=8), DIMENSION(rows,cols) :: a
  REAL(KIND=8), DIMENSION(rows,cols) :: b

  ! MPI variables
  INTEGER  :: nprocs
  INTEGER  :: myrank
  INTEGER, DIMENSION(4)                  :: requests
  INTEGER, DIMENSION(MPI_STATUS_SIZE, 4) :: statuses
  INTEGER  :: ierr

  ! Count variables
  INTEGER :: i, j, count
  INTEGER :: jsta, jend, jsta2, jend2

  ! Initialize MPI
  CALL MPI_INIT(ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)

  ! Calculate the range (jsta, jend) on which this process operates
  CALL para_range(1, cols, nprocs, myrank, jsta, jend)

  ! Initialize the matrix a
  DO j = jsta, jend
    DO i = 1, rows
      a(i,j) = i + 10.0 * j
    ENDDO
  ENDDO

  count = 0
  !  Data exchange with process myrank-1
  IF (myrank > 0) THEN
    CALL MPI_ISEND(a(1,jsta), rows, MPI_REAL8, myrank-1, 1, MPI_COMM_WORLD, &
                   requests(count+1), ierr)
    CALL MPI_IRECV(a(1,jsta-1), rows, MPI_REAL8, myrank-1, 1, MPI_COMM_WORLD, &
                   requests(count+2), ierr)
    count = count + 2
  ENDIF

  !  Data exchange with process myrank+1
  IF (myrank < nprocs-1) THEN
    CALL MPI_ISEND(a(1,jend), rows, MPI_REAL8, myrank+1, 1, MPI_COMM_WORLD, &
                   requests(count+1), ierr)
    CALL MPI_IRECV(a(1,jend+1), rows, MPI_REAL8, myrank+1, 1, MPI_COMM_WORLD, &
                   requests(count+2), ierr)
    count = count + 2
  ENDIF

  ! Take process 0 and process nprocs-1 into account, when updating b
  jsta2 = jsta
  jend2 = jend
  IF (myrank == 0) jsta2 = 2
  IF (myrank == nprocs - 1) jend2 = cols - 1

  ! Wait until all data exchanges have taken place
  CALL MPI_WAITALL(count, requests, statuses, ierr)

  ! Update the matrix b
  DO j = jsta2, jend2
    DO i = 2, rows - 1
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

