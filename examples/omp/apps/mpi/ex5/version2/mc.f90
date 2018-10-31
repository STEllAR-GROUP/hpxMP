PROGRAM MonteCarlo2
  ! This program demonstrates the parallelization of a program that uses the
  ! Monte Carlo method by simulating a random walk in two dimensions of 100,000
  ! particles in 10 steps. The program outputs the distribution of the 
  ! distances that the particles have travled.

  USE IFPORT

  IMPLICIT NONE
  INCLUDE 'mpif.h'

  ! Configuration variables
  INTEGER, PARAMETER      :: n = 100000
  REAL, PARAMETER         :: pi = 3.1415926
  INTEGER, DIMENSION(0:9) :: localDist, globalDist

  ! MPI variables
  INTEGER               :: nprocs
  INTEGER               :: myrank
  INTEGER               :: ierr

  ! Count and temporary variables
  INTEGER :: i, ista, iend, step, temp
  REAL    :: x, y, angle

  CALL MPI_INIT(ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)

  CALL para_range(1, n, nprocs, myrank, ista, iend)

  DO i = 0, 9
    localDist(i) = 0
  ENDDO

  CALL srand(100 + myrank)
  DO i = ista, iend
    x = 0.0
    y = 0.0
    DO step = 1, 10
      angle = 2.0 * pi * rand()
      x = x + cos(angle)
      y = y + sin(angle)
    ENDDO
    temp = sqrt(x**2 + y**2)
    localDist(temp) = localDist(temp) + 1
  ENDDO
  CALL MPI_REDUCE(localDist, globalDist, 10, MPI_INTEGER, MPI_SUM, 0, &
                  MPI_COMM_WORLD, ierr)

  IF (myrank == 0) write (*,*) 'distribution =', globalDist

  CALL MPI_FINALIZE(ierr)
END PROGRAM MonteCarlo2


SUBROUTINE para_range(n1, n2, nprocs, irank, ista, iend)
  IMPLICIT NONE

  INTEGER, INTENT(IN)  :: n1
  INTEGER, INTENT(IN)  :: n2
  INTEGER, INTENT(IN)  :: nprocs
  INTEGER, INTENT(IN)  :: irank
  INTEGER, INTENT(OUT) :: ista
  INTEGER, INTENT(OUT) :: iend

  INTEGER :: iwork1
  INTEGER :: iwork2

  iwork1 = (n2 - n1 + 1) / nprocs
  iwork2 = MOD(n2 - n1 + 1, nprocs)
  ista = irank * iwork1 + n1 + MIN(irank, iwork2)
  iend = ista + iwork1 - 1
  IF (iwork2 > irank) iend = iend + 1
END
