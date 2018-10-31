Program Finite_Element

  ...

  PARAMETER(iemax = 12, inmax = 21)
  REAL*8 ve(iemax), vn(inmax)
  INTEGER index(4,iemax)

  INCLUDE 'mpif.h'

  PARAMETER (ncpu = 3)
  INTEGER nprocs, myrank
  INTEGER istatus(MPI_STATUS_SIZE)
  INTEGER itemp(inmax,0:ncpu-1)
  INTEGER incnt(0:ncpu-1), inwork(inmax,0:ncpu-1)
  INTEGER ibcnt1(0:ncpu-1), ibwork1(inmax,0:ncpu-1)
  INTEGER ibcnt2(0:ncpu-1), ibwork2(inmax,0:ncpu-1)
  INTEGER iiesta(0:ncpu-1), iiecnt(0:ncpu-1)
  INTEGER ireqs(0:ncpu-1), ireqr(0:ncpu-1)
  DIMENSION bufs(inmax,0:ncpu-1), bufr(inmax,0:ncpu-1)

  ...

  CALL MPI_INIT(ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD, myrank, ierr)

  DO irank = 0, nprocs - 1
    DO i = 1, inmax
      itemp(i,irank) = 0
    ENDDO
    ibcnt1(irank) = 0
    ibcnt2(irank) = 0
    incnt(irank) = 0
  ENDDO

  DO irank = 0, nprocs - 1
    CALL para_range(1, iemax, nprocs, irank, iesta, ieend)
    iiesta(irank) = iesta
    iiecnt(irank) = ieend - iesta + 1

    DO ie = iesta, ieend
      DO j = 1, 4
        itemp(index(j,ie),irank) = 1
      ENDDO
    ENDDO
  ENDDO

  CALL para_range(1, iemax, nprocs, myrank, iesta, ieend)

  DO i = 1, inmax
    iflg = 0
    DO irank = 0, nprocs - 1
      IF (itemp(i,irank) == 1) THEN
        IF (iflg == 0) THEN
          iflg = 1
          iirank = irank
        ELSE
          itemp(i,irank) = 0
          IF (irank == myrank) THEN
            ibcnt1(iirank) = ibcnt1(iirank) + 1
            ibwork1(ibcnt1(iirank),iirank) = i
          ELSEIF (iirank == myrank) THEN
            ibcnt2(irank) = ibcnt2(irank) + 1
            ibwork2(ibcnt2(irank),irank) = i
          ENDIF
        ENDIF
      ENDIF
    ENDDO
  ENDDO
  DO irank = 0, nprocs - 1
    DO i = 1, inmax
       IF (itemp(i,irank) == 1) THEN
         incnt(irank) = incnt(irank) + 1
         inwork(incnt(irank),irank) = i
       ENDIF
    ENDDO
  ENDDO
  DO ie = iesta, ieend
    ve(ie) = ie * 10.0
  ENDDO
  DO i = 1, incnt(myrank)
    in = inwork(i,myrank)
    vn(in) = in * 100.0
  ENDDO

  DO itime = 1, 10
    DO irank = 0, nprocs - 1
      DO i = 1, ibcnt1(irank)
        vn(ibwork1(i,irank)) = 0.0
      ENDDO
    ENDDO
    DO ie = iesta, ieend
      DO j = 1, 4
        vn(index(j,ie)) = vn(index(j,ie)) + ve(ie)
      ENDDO
    ENDDO
    DO irank = 0, nprocs - 1
      DO i = 1, ibcnt1(irank)
        bufs(i,irank) = vn(ibwork1(i,irank))
      ENDDO
    ENDDO
    DO irank = 0, nprocs - 1
      IF (ibcnt1(irank) /= 0)
        CALL MPI_ISEND(bufs(1,irank),ibcnt1(irank),MPI_REAL8,irank,1, &
                       MPI_COMM_WORLD,ireqs(irank),ierr)
      IF (ibcnt2(irank) /= 0)
         CALL MPI_IRECV(bufr(1,irank),ibcnt2(irank),MPI_REAL8,irank,1, &
                       MPI_COMM_WORLD,ireqr(irank),ierr)
    ENDDO
    DO irank = 0, nprocs - 1
      IF (ibcnt1(irank) /= 0) CALL MPI_WAIT(ireqs(irank),istatus,ierr)
      IF (ibcnt2(irank) /= 0) CALL MPI_WAIT(ireqr(irank),istatus,ierr)
    ENDDO
    DO irank = 0, nprocs - 1
      DO i = 1, ibcnt2(irank)
        vn(ibwork2(i,irank)) = vn(ibwork2(i,irank)) + bufr(i,irank)
      ENDDO
    ENDDO

    DO i = 1, incnt(myrank)
      in = inwork(i,myrank)
      vn(in) = vn(in) * 0.25
    ENDDO
    DO irank = 0, nprocs - 1
      DO i = 1, ibcnt2(irank)
        bufs(i,irank) = vn(ibwork2(i,irank))
      ENDDO
    ENDDO
    DO irank = 0, nprocs - 1
      IF (ibcnt2(irank) /= 0)
        CALL MPI_ISEND(bufs(1,irank),ibcnt2(irank),MPI_REAL8,irank,1, &
                       MPI_COMM_WORLD,ireqs(irank),ierr)
      IF (ibcnt1(irank) /= 0)
        CALL MPI_IRECV(bufr(1,irank),ibcnt1(irank),MPI_REAL8,irank,1, &
                       MPI_COMM_WORLD,ireqr(irank),ierr)
    ENDDO
    DO irank = 0, nprocs - 1
      IF (ibcnt2(irank) /= 0) CALL MPI_WAIT(ireqs(irank),istatus,ierr)
      IF (ibcnt1(irank) /= 0) CALL MPI_WAIT(ireqr(irank),istatus,ierr)
    ENDDO
    DO irank = 0, nprocs - 1
      DO i = 1, ibcnt1(irank)
        vn(ibwork1(i,irank)) = bufr(i,irank)
      ENDDO
    ENDDO

    DO ie = iesta, ieend
      DO j=1,4
        ve(ie) = ve(ie) + vn(index(j,ie))
      ENDDO
    ENDDO
    DO ie = iesta, ieend
      ve(ie) = ve(ie) * 0.25
    ENDDO
  ENDDO

  DO i = 1, incnt(myrank)
    bufs(i,myrank) = vn(inwork(i,myrank))
  ENDDO
  IF (myrank == 0) THEN
    DO irank = 1, nprocs - 1
      CALL MPI_IRECV(bufr(1,irank),incnt(irank),MPI_REAL8,irank,1, &
                     MPI_COMM_WORLD,ireqs(irank),ierr)
    ENDDO
    DO irank = 1, nprocs - 1
      CALL MPI_WAIT(ireqs(irank),istatus,ierr)
    ENDDO
  ELSE
    CALL MPI_ISEND(bufs(1,myrank),incnt(myrank),MPI_REAL8,0,1, &
                   MPI_COMM_WORLD,ireqr,ierr)
    CALL MPI_WAIT(ireqr,istatus,ierr)
  ENDIF
  IF (myrank == 0) THEN
    DO irank = 1, nprocs - 1
      DO i = 1, incnt(irank)
        vn(inwork(i,irank)) = bufr(i,irank)
      ENDDO
    ENDDO
  ENDIF
  IF (myrank == 0) THEN
    DO irank = 1, nprocs - 1
      CALL MPI_IRECV(ve(iiesta(irank)),iiecnt(irank),MPI_REAL8,irank,1, &
                     MPI_COMM_WORLD,ireqs(irank),ierr)
    ENDDO
    DO irank = 1, nprocs - 1
      CALL MPI_WAIT(ireqs(irank),istatus,ierr)
    ENDDO
  ELSE
    CALL MPI_ISEND(ve(iesta),ieend-iesta+1,MPI_REAL8,0,1, &
                   MPI_COMM_WORLD,ireqr,ierr)
    CALL MPI_WAIT(ireqr,istatus,ierr)
  ENDIF
  CALL MPI_FINALIZE(ierr)
  PRINT *,’Result’,vn,ve

  ...
END PROGRAM Finite_Element
