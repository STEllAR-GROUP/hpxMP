PROGRAM MolecularDynamics3
  ! This program demonstrates parallelization of a molecular dynamics program.
  ! In this program, most of the time is used in the 2 inner most loops that 
  ! calculate the force between 2 particles.
  ! In this case, the inner of these 2 loops is parallelized.

  USE IFPORT

  IMPLICIT NONE
  INCLUDE 'mpif.h'

  ! Configuration
  INTEGER, PARAMETER :: n = 10
  REAL, DIMENSION(n) ::  f, x, ff
  
  ! MPI variables
  INTEGER               :: nprocs
  INTEGER               :: myrank
  INTEGER               :: ierr

  ! Count and temporary variables
  INTEGER :: t, i, j, irank
  REAL    :: fij
  
  CALL MPI_INIT(ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)

  ! Initialize
  CALL srand(100)
  DO i = 1, n
    x(i) = 50.0*rand()
  ENDDO

  IF (myrank == 0) write (*,*) "x = ", x

  ! The main loop
  DO t = 1, 2
    DO i = 1, n
      f(i) = 0.0
    ENDDO
    irank = -1
    DO i = 1, n-1
      DO j = i+1, n
        irank = irank + 1
        IF (irank == nprocs) irank = 0
        IF (myrank == irank) THEN
          fij = 1.0 / (x(j)-x(i))
          f(i) = f(i) + fij
          f(j) = f(j) - fij
        ENDIF
      ENDDO
    ENDDO
    CALL MPI_ALLREDUCE(f, ff, n, MPI_REAL, MPI_SUM, MPI_COMM_WORLD, ierr)
    DO i = 1, n
      x(i) = x(i) + ff(i)
    ENDDO

    IF (myrank == 0) write (*,*) "x = ", x
  ENDDO
  
  CALL MPI_FINALIZE(ierr)
END PROGRAM MolecularDynamics3
