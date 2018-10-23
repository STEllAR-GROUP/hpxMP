PROGRAM MolecularDynamics1
  ! This program demonstrates a serial molecular dynamics program.
  ! In this program, most of the time is used in the 2 inner most loops that 
  ! calculate the force between 2 particles.

  USE IFPORT

  IMPLICIT NONE

  ! Configuration
  INTEGER, PARAMETER :: n = 10
  REAL, DIMENSION(n) ::  f, x

  ! Count and temporary variables
  INTEGER :: t, i, j
  REAL    :: fij

  ! Initialize
  CALL srand(100)
  DO i = 1, n
    x(i) = 50.0*rand()
  ENDDO

  write (*,*) "x = ", x

  ! The main loop
  DO t = 1, 2
    DO i = 1, n
      f(i) = 0.0
    ENDDO

    ! Hotspot
    DO i = 1, n-1
      DO j = i+1, n
        fij = 1.0 / (x(j)-x(i))
        f(i) = f(i) + fij
        f(j) = f(j) - fij
      ENDDO
    ENDDO

    DO i = 1, n
      x(i) = x(i) + f(i)
    ENDDO

    write (*,*) "x = ", x
  ENDDO
END PROGRAM MolecularDynamics1
