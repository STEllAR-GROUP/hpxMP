FF     = mpif90
FFLAGS = -O2
PRG    = md
LIBS   = -limf -lm

all: $(PRG)

%: %.f90 Makefile
	$(FF) $(FFLAGS) $(PRG).f90 -o $@ $(LIBS)

clean:
	rm -f $(PRG) ex6.3.*
