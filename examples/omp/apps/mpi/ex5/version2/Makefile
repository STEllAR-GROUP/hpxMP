FF     = mpif90
FFLAGS = -O0 -g
PRG    = mc
LIBS   = -limf -lm

all: $(PRG)

%: %.f90 Makefile
	$(FF) $(FFLAGS) $(PRG).f90 -o $@ $(LIBS)

clean:
	rm -f $(PRG) ex5.*
