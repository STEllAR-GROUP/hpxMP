FF     = mpif90
FFLAGS = -O2
PRG    = sor3
LIBS   = -limf -lm

$(PRG): main.f90 grid.o
	$(FF) $(FFLAGS) -o $@ main.f90 grid.o $(LIBS)

grid.o: grid.f90
	$(FF) $(FFLAGS) -c grid.f90

clean:
	rm -f $(PRG) *.o *.mod ex4.3.*
