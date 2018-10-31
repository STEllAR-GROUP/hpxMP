PROGRAM Finite_Element
  ! This program demonstrates the parallelization of a program that is based
  ! on the Finite Element Method. In this program, nodes and elements are
  ! distributed in the following way:
  ! 
  ! N   N   N   N
  !   E   E   E
  ! N   N   N   N
  !   E   E   E
  ! N   N   N   N
  !
  ! The procedure inside of the main loop of this program is:
  ! 1. The value of each element is added to the closest surrounding nodes.
  ! 2. The value of each nodes is divided by 4
  ! 3. The value of each node is added to the closest surrounding elements.
  ! 4. The value of each element is divided by 4

  USE Grid
  IMPLICIT NONE

  INTEGER :: step         ! The time steps
  INTEGER :: r            ! rows
  INTEGER :: c            ! columns

  CALL initialize()

  ! Initialize the inner element grid
  DO r=1, rows
    DO c=1, localCols
      elements(r, c) = (r + (c-1)*rows + myrank*rows*localCols) * 10.0
    END DO
  END DO

  ! Initialize the nodes that surround the elements
  DO r=1, rows+1
    DO c=1, localCols+1
      nodes(r, c) = (c + myrank*localCols + (r-1)*(cols+1)) * 100.0
    END DO
  END DO

  CALL printGrids("Initial configuration")

  ! The main loop
  main: DO step=1, 2
    ! Elements -> nodes
    CALL synchronizeElements()
    DO r=1, rows
      DO c=1, localCols
        nodes(r  ,c  ) = nodes(r  ,c  ) + elements(r,c)
        nodes(r  ,c+1) = nodes(r  ,c+1) + elements(r,c)
        nodes(r+1,c  ) = nodes(r+1,c  ) + elements(r,c)
        nodes(r+1,c+1) = nodes(r+1,c+1) + elements(r,c)
      END DO
      IF (myrank < nprocs-1) THEN
        c = localCols+1
        nodes(r  ,c) = nodes(r  ,c) + elements(r,c)
        nodes(r+1,c) = nodes(r+1,c) + elements(r,c)
      ENDIF
    END DO

    CALL printGrids("Elements->nodes")

    ! Update nodes
    DO r=1, rows+1
      DO c=1, localCols+1
        nodes(r,c) = nodes(r,c) * 0.25
      END DO
    END DO

    CALL printGrids("Update nodes")

    ! Nodes -> elements
    CALL synchronizeNodes()
    DO r=1, rows
      DO c=1, localCols
        elements(r,c) = elements(r,c) + nodes(r,c) + nodes(r,c+1) + &
                        nodes(r+1,c) + nodes(r+1,c+1)
      END DO
    END DO

    CALL printGrids("Nodes->elements")

    ! Update elements
    DO r=1, rows
      DO c=1, localCols
        elements(r,c) = elements(r,c) * 0.25
      END DO
    END DO

    CALL printGrids("Update elements")
  END DO main

  CALL finalize()

END PROGRAM Finite_Element
