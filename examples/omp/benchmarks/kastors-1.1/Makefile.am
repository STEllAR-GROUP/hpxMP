
# flags to aclocal if Makefile rules trigger it
ACLOCAL_AMFLAGS=-I m4

SUBDIRS = 

EXTRA_DIST=common/main.c common/main.h common/timer.h

if COMPILE_STRASSEN
SUBDIRS += strassen
endif

if COMPILE_JACOBI
SUBDIRS += jacobi
endif

if COMPILE_SPARSELU
SUBDIRS += sparselu
endif

if COMPILE_PLASMA
SUBDIRS += plasma
endif

OUT=./measures_$(CXX)

run:
	@rm $(OUT) -rfi || true;
	@for folder in ${SUBDIRS};\
	do\
		OUT=../$(OUT) make -C $$folder run;\
	done
	@echo -e "\n\nPlain data can be found in : $(OUT)\n \n";

htdoc_dir=${top_srcdir}/htdocs

deploy: dist
	rsync -az --no-perms --no-times --no-group $(htdoc_dir) scm.gforge.inria.fr:/home/groups/kastors
