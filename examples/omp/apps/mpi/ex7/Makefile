FF     = mpif90
FFLAGS = -O2
PRG    = master worker
LIBS   = -limf -lm

all: $(PRG)

master: master.f90
	$(FF) $(FFLAGS) $< -o $@ $(LIBS)

worker: worker.f90
	$(FF) $(FFLAGS) worker.f90 -o $@ $(LIBS)

clean:
	rm -f $(PRG) ex7.*
