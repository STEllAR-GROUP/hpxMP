PROGRAM SOR1
  ! This program demonstrates the parallelization of a program that solves
  ! the 2D Laplace equation using the successive over-relaxtion (SOR) method. 
  ! In this example, the red-black SOR method is used.

  USE grid
  IMPLICIT NONE
  INCLUDE 'mpif.h'

  ! MPI variables
  INTEGER ierr
  
  ! Count variables
  INTEGER :: r, c, step

  ! Math variables
  REAL(KIND=8) :: omega, temp, err1, err2, eps

  CALL initialize()

  ! Initialization of the problem
  DO r=0, rows+1
    DO c=0, localCols+1
!      x(r,c) = r + c*(rows+2) + myrank*(rows+2)*localCols
      x(r,c) = MOD(r + c + myrank*localCols, 2)
    END DO
  END DO

  omega = 1.0
  eps   = 0.001

  CALL printGrid("Initial configuration")

  ! The main loop
  DO step = 1, 300
    err1 = 0.0
    
    ! Update first half 
    CALL synchronize(0)
    DO c = 1, localCols
      DO r = 1+MOD(even1+c-1,2), rows, 2
        temp = 0.25 * (x(r,c-1) + x(r-1,c) + x(r+1,c) + x(r,c+1)) - x(r,c)
        x(r,c) = x(r,c) + omega * temp
        IF (abs(temp) > err1) err1 = abs(temp)
      ENDDO
    ENDDO

    CALL printGrid("After first update")

    ! Update second half 
    CALL synchronize(1)
    DO c = 1, localCols
      DO r = 1+MOD(odd1+c-1,2), rows, 2
        temp = 0.25 * (x(r,c-1) + x(r-1,c) + x(r+1,c) + x(r,c+1)) - x(r,c)
        x(r,c) = x(r,c) + omega * temp
        IF (abs(temp) > err1) err1 = abs(temp)
      ENDDO
    ENDDO

    CALL printGrid("After second update")

    CALL MPI_ALLREDUCE(err1, err2, 1, MPI_REAL8, MPI_MAX, MPI_COMM_WORLD, ierr)
    err1 = err2
    IF (myrank == 0) THEN
      write(*,*) "step: ", step
      write(*,*) "error: ", err1
    ENDIF
    IF (err1 <= eps) exit
  ENDDO

  CALL finalize()
END
