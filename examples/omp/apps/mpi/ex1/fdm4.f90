PROGRAM FDM4
  ! This program demonstrates the parallelization of a program using the 
  ! 2D Finite Difference Method (FDM). In this example, block-distribution 
  ! in both dimensions is used and the value of b(i,j) is calculated from 
  ! the eight neighbors including the four diagonals.

  IMPLICIT NONE
  INCLUDE 'mpif.h'

  ! Configuration variables
  INTEGER, PARAMETER :: rows = 12
  INTEGER, PARAMETER :: cols = 9
  INTEGER, PARAMETER :: iprocs = 3    ! Process rows
  INTEGER, PARAMETER :: jprocs = 3    ! Process columns
  REAL(KIND=8), DIMENSION(rows,cols) :: a
  REAL(KIND=8), DIMENSION(rows,cols) :: b

  ! Send and receive buffers
  REAL(KIND=8), DIMENSION(cols) :: sndbuf1
  REAL(KIND=8), DIMENSION(cols) :: sndbuf2
  REAL(KIND=8), DIMENSION(cols) :: rcvbuf1
  REAL(KIND=8), DIMENSION(cols) :: rcvbuf2

  ! MPI variables
  INTEGER :: nprocs
  INTEGER :: myrank
  INTEGER, DIMENSION(4)                  :: requests
  INTEGER, DIMENSION(MPI_STATUS_SIZE, 4) :: statuses
  INTEGER :: ierr
  INTEGER :: irank, jrank
  INTEGER :: iprev, inext, jprev, jnext

  ! Count variables
  INTEGER :: i, j
  INTEGER :: ista, iend, ista2, iend2, ista3, iend3, ilen
  INTEGER :: jsta, jend, jsta2, jend2, jsta3, jend3, jlen

  ! Index table
  INTEGER itable(-1:iprocs, -1:jprocs)

  ! Initialize MPI
  CALL MPI_INIT(ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)

  ! Do we have the right number of processes?
  IF (nprocs /= iprocs * jprocs) THEN
    IF (myrank == 0) THEN
      WRITE (*,*) 'Error: run this program on ', iprocs*jprocs, ' processes'
    ENDIF
    CALL MPI_Abort(MPI_COMM_WORLD, 1)
  ENDIF

  ! Create an index table for looking up who the neighbouring processes are
  DO j = -1, jprocs
    DO i = -1, iprocs
      itable(i,j) = MPI_PROC_NULL
    ENDDO
  ENDDO
  DO i = 0, iprocs - 1
    DO j = 0, jprocs - 1
      itable(i,j) = i*iprocs + j
    ENDDO
  ENDDO

  ! This process's position in the index table
  irank = myrank / jprocs
  jrank = MOD(myrank, jprocs)

  ! Calculate which part of matrix a that this process controls
  CALL para_range(1, cols, jprocs, jrank, jsta, jend)
  CALL para_range(1, rows, iprocs, irank, ista, iend)

  DO j = jsta, jend
    DO i = ista, iend
      a(i,j) = i + 10.0 * j
    ENDDO
  ENDDO

  ! Variables used in the MPI communication
  ilen = iend - ista + 1
  jlen = jend - jsta + 1
  jnext = itable(irank, jrank + 1)
  jprev = itable(irank, jrank - 1)
  inext = itable(irank + 1, jrank)
  iprev = itable(irank - 1, jrank)

  ! Left
  CALL MPI_ISEND(a(ista,jsta),   ilen, MPI_REAL8, jprev, 1, MPI_COMM_WORLD, &
                 requests(1), ierr)
  CALL MPI_IRECV(a(ista,jsta-1), ilen, MPI_REAL8, jprev, 1, MPI_COMM_WORLD, &
                 requests(2), ierr)

  ! Right
  CALL MPI_ISEND(a(ista,jend),   ilen, MPI_REAL8, jnext, 1, MPI_COMM_WORLD, &
                 requests(3), ierr)
  CALL MPI_IRECV(a(ista,jend+1), ilen, MPI_REAL8, jnext, 1, MPI_COMM_WORLD, &
                 requests(4), ierr)

  ! Include the corner elements when sending and receiving data
  jsta2 = MAX(1,    jsta - 1)
  jend2 = MIN(cols, jend + 1)

  ! Wait until all data exchanges have taken place
  CALL MPI_WAITALL(4, requests, statuses, ierr)

  ! Copy 2 rows from matrix a to the send buffer arrays
  IF (irank > 0)          sndbuf1(jsta2:jend2) = a(ista, jsta2:jend2)
  IF (irank < iprocs - 1) sndbuf2(jsta2:jend2) = a(iend, jsta2:jend2)

  ! Up
  CALL MPI_ISEND(sndbuf1(jsta2), jlen, MPI_REAL8, iprev, 1, MPI_COMM_WORLD, &
                 requests(1), ierr)
  CALL MPI_IRECV(rcvbuf1(jsta2), jlen, MPI_REAL8, iprev, 1, MPI_COMM_WORLD, &
                 requests(2), ierr)

  ! Down
  CALL MPI_ISEND(sndbuf2(jsta2), jlen, MPI_REAL8, inext, 1, MPI_COMM_WORLD, &
                 requests(3), ierr)
  CALL MPI_IRECV(rcvbuf2(jsta2), jlen, MPI_REAL8, inext, 1, MPI_COMM_WORLD, &
                 requests(4), ierr)

  ! Take the end points in both dimensions into account, when updating b
  jsta3 = jsta
  jend3 = jend
  IF (jrank == 0)          jsta3 = 2
  IF (jrank == jprocs - 1) jend3 = cols - 1

  ista3 = ista
  iend3 = iend
  IF (irank == 0)          ista3 = 2
  IF (irank == iprocs - 1) iend3 = rows - 1

  ! Wait until all data exchanges have taken place
  CALL MPI_WAITALL(4, requests, statuses, ierr)

  ! Copy 2 rows from the receive buffers to the matrix a
  IF (irank > 0)          a(ista-1,jsta2:jend2) = rcvbuf1(jsta2:jend2)
  IF (irank < iprocs - 1) a(iend+1,jsta2:jend2) = rcvbuf2(jsta2:jend2)

  ! Update the matrix b
  DO j = jsta3, jend3
    DO i = ista3, iend3
      b(i,j) = a(i-1,j )  + a(i, j-1)  + a(i, j+1)  + a(i+1,j ) + &
               a(i-1,j-1) + a(i+1,j-1) + a(i-1,j+1) + a(i+1,j+1)
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
