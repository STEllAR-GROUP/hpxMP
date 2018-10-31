PROGRAM LU
  ! This program demonstrates LU factorization (actually just Gaussian 
  ! Elimination) by solving the following equation system:
  ! 
  ! |  2  1 -1 |     |   8 |
  ! | -3 -1  2 | X = | -11 |
  ! | -2  1  2 |     |  -3 |
  !
  ! The solution to this equation is:
  !
  !     |  2 |
  ! X = |  3 |
  !     | -1 |

  IMPLICIT NONE
  INCLUDE 'mpif.h'

  ! Configuration variables
  INTEGER, PARAMETER   :: n = 3
  REAL, DIMENSION(n,n) :: a = &
        RESHAPE ( (/ 2, -3, -2, 1, -1, 1, -1, 2, 2 /), (/3,3/) )
  REAl, DIMENSION(n)   :: b = (/ 8, -11, -3 /)

  ! MPI variables
  INTEGER               :: nprocs
  INTEGER               :: myrank
  INTEGER               :: ierr
  INTEGER, DIMENSION(n) :: map       ! column to process

  ! Count and temporary variables
  INTEGER :: i, ii, j, k, offset
  REAL    :: s, ss

  ! Initialize MPI
  CALL MPI_INIT(ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)

  ! Assign the column in a to the processes in a cylic manner
  DO i = 0, n
    map(i+1) = MOD(i, nprocs)
  ENDDO

  ! LU factorization
  DO k = 1, n
    IF (map(k) == myrank) THEN
      DO i = k+1, n
        a(i,k) = a(i,k) / a(k,k)
      ENDDO
    ENDIF
    CALL MPI_BCAST(a(k,k), n-k+1, MPI_REAL, map(k), MPI_COMM_WORLD, ierr)
    DO j = k+1, n
      IF (map(j) == myrank) THEN
        DO i = k+1, n
          a(i,j) = a(i,j) - a(i,k) * a(k,j)
        ENDDO
      ENDIF
    ENDDO
  ENDDO

  ! Forward elimination
  DO i = 2, n
    s = 0.0
    ! Process 0 owns column 1, process 1 owns column 2, etc. 
    DO j = 1 + myrank, i - 1, nprocs
      s = s + a(i,j) * b(j)
    ENDDO
    CALL MPI_ALLREDUCE(s, ss, 1, MPI_REAL, MPI_SUM, MPI_COMM_WORLD, ierr)
    b(i) = b(i) - ss
  ENDDO

  ! Backward substitution
  DO i = n, 1, -1
    ! Starting from column i+1, find the first column that this process owns
    offset = myrank - map(i+1)
    IF (offset < 0) THEN
      offset = offset + nprocs
    ENDIF
    ii = i + 1 + offset

    s = 0.0
    DO j = ii, n, nprocs
      s = s + a(i, j) * b(j)
    ENDDO
    CALL MPI_ALLREDUCE(s, ss, 1, MPI_REAL, MPI_SUM, MPI_COMM_WORLD, ierr)
    b(i) = (b(i) - ss) / a(i,i)
  ENDDO

  IF (myrank == 0) write (*,*) "x = (", b, ")"

  CALL MPI_Finalize(ierr)
END PROGRAM LU
