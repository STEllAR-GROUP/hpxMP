FF     = ifort
FFLAGS = -O2
PRG    = mc

all: $(PRG)

%: %.f90 Makefile
	$(FF) $(FFLAGS) $(PRG).f90 -o $@

clean:
	rm -f $(PRG)
