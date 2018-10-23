FF     = mpif90
FFLAGS = -O2
PRG    = fdm1 fdm2 fdm3 fdm4
LIBS   = -limf -lm

all: $(PRG)

%: %.f90
	$(FF) $(FFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f $(PRG) ex1.*
