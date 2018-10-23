FF     = mpif90
FFLAGS = -O2
LIBS   = -limf -lm

fem: main.f90 grid.o Makefile
	$(FF) $(FFLAGS) -o $@ main.f90 grid.o $(LIBS)

grid.o: grid.f90
	$(FF) $(FFLAGS) -c grid.f90

clean:
	rm -f fem *.o *.mod ex2.*
