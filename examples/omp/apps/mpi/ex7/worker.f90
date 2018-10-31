PROGRAM Worker
  ! This program demonstrates how to use the MPMD (Multiple Programs Multiple
  ! Data) model. In this case, a master/worker MPMD program is demonstrated.

  IMPLICIT NONE
  INCLUDE 'mpif.h'
     
  ! MPI variables
  INTEGER :: nprocs, myrank, tag, dummy, err
  INTEGER, DIMENSION(MPI_STATUS_SIZE) :: status

  ! Count variables
  INTEGER job

  CALL MPI_INIT(err)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, err)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, err)

  ! The main loop
  tag   = 1
  dummy = 0
  DO
    CALL MPI_SEND(dummy, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, err)
    CALL MPI_RECV(job, 1, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, status, err)
    IF (job == -1) EXIT

    write (*,*) "Worker ", myrank, " does work number ", job

    ! The work that the workers do
    CALL sleep(1)
  ENDDO
    
  CALL MPI_FINALIZE(err)
END PROGRAM Worker
