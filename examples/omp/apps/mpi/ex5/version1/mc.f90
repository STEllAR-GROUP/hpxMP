PROGRAM MonteCarlo1
  ! This program demonstrates a serial Monte Carlo method by simulating a 
  ! random walk in two dimensions of 100,000 particles in 10 steps. The program
  ! outputs the distribution of the distances that the particles have travled.

  USE IFPORT

  IMPLICIT NONE

  INTEGER, PARAMETER      :: n = 100000
  INTEGER, DIMENSION(0:9) :: total

  REAL    :: pi, x, y, angle
  INTEGER :: i, step, temp

  pi = 3.1415926
  DO i = 0, 9
    total(i) = 0
  ENDDO

  CALL srand(100)
  DO i = 1, n
    x = 0.0
    y = 0.0
    DO step = 1, 10
      angle = 2.0 * pi * rand()
      x = x + cos(angle)
      y = y + sin(angle)
    ENDDO

    temp = sqrt(x**2 + y**2)
    total(temp) = total(temp) + 1
  ENDDO

  write (*,*) 'total =', total
END PROGRAM MonteCarlo1
