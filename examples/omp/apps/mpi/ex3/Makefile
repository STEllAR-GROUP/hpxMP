FF     = mpif90
FFLAGS = -O2
PRG    = lu
LIBS   = -limf -lm

all: $(PRG)

%: %.f90
	$(FF) $(FFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f $(PRG) ex3.*
