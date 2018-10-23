PROGRAM Master
  ! This program demonstrates how to use the MPMD (Multiple Programs Multiple
  ! Data) model. In this case, a master/worker MPMD program is demonstrated.

  IMPLICIT NONE
  INCLUDE 'mpif.h'
  
  ! Configuration
  INTEGER, PARAMETER :: njobmax = 10
    
  ! MPI variables
  INTEGER :: nprocs, myrank, tag, dummy, err, dest
  INTEGER, DIMENSION(MPI_STATUS_SIZE) :: status

  ! Count variables
  INTEGER job, i

  CALL MPI_INIT(err)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, err)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, err)

  ! Distribute the work among the workers
  tag = 1
  DO job = 1, njobmax
    CALL MPI_RECV(dummy, 1, MPI_INTEGER, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &
                  status, err)
    dest = status(MPI_SOURCE)
    CALL MPI_SEND(job, 1, MPI_INTEGER, dest, tag, MPI_COMM_WORLD, err)
  ENDDO

  ! Tell the workers to stop
  DO i = 1, nprocs-1 
    CALL MPI_RECV(dummy, 1, MPI_INTEGER, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &
                  status, err)
    dest = status(MPI_SOURCE)
    CALL MPI_SEND(-1, 1, MPI_INTEGER, dest, tag, MPI_COMM_WORLD, err)
  ENDDO
    
  CALL MPI_FINALIZE(err)
END PROGRAM Master
