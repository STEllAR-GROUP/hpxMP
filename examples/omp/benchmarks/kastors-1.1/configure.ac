AC_INIT([KaStORS],[1.1],[kastors-user@lists.gforge.inria.fr])
dnl AC_CONFIG_AUX_DIR: not before, not after
dnl http://www.mail-archive.com/autoconf@gnu.org/msg07824.html
AC_CONFIG_AUX_DIR([build-aux])
AC_CANONICAL_TARGET
AC_CONFIG_SRCDIR([sparselu/src/sparselu.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_LINKS([run.sh:run.sh])
AM_INIT_AUTOMAKE([subdir-objects foreign 1.9 tar-pax])
dnl Require Autoconf v2.62 for the AC_OPENMP macro
AC_PREREQ([2.62])

AC_PROG_CC(gcc icc clang llvm cc)
AC_PROG_CC_C99
AC_PROG_RANLIB

dnl Optimistic scenario!
KASTORS_COMPILE_STRASSEN=yes
KASTORS_COMPILE_SPARSELU=yes
KASTORS_COMPILE_PLASMA=yes

AC_LANG([C])
dnl Check for OpenMP support
AC_OPENMP
if test "$ac_cv_prog_c_openmp" = "unsupported";
then
        AC_MSG_ERROR([it appears your $CC compiler does not support OpenMP. Aborting.])
fi

saved_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS $OPENMP_CFLAGS"
dnl Check for the support of OpenMP task dependencies
AC_MSG_CHECKING([for $CC to support OpenMP task dependencies])
AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([[int x;]],[[#pragma omp task depend(out: x)
  x = 10;]])],
        [OMP_DEP=yes],
        [OMP_DEP=no]
)

if test "$OMP_DEP" = "yes";
then
        AC_MSG_RESULT([yes])
else
        AC_MSG_RESULT([no])
        AC_MSG_ERROR([it appears your $CC compiler does not support OpenMP task dependencies. Aborting.])
fi

CFLAGS="$saved_CFLAGS -O2 -g"

dnl Add possibility to disable jacobi
AC_ARG_ENABLE([jacobi],
              AS_HELP_STRING([--disable-jacobi], [Disable jacobi benchs]))
KASTORS_COMPILE_JACOBI=no
AS_IF([test "x$enable_jacobi" != "xno"], [
KASTORS_COMPILE_JACOBI=yes
     ])

dnl Add possibility to disable strassen
AC_ARG_ENABLE([strassen],
              AS_HELP_STRING([--disable-strassen], [Disable strassen benchs]))
KASTORS_COMPILE_STRASSEN=no
AS_IF([test "x$enable_strassen" != "xno"], [
KASTORS_COMPILE_STRASSEN=yes
     ])

dnl Add possibility to disable sparselu
AC_ARG_ENABLE([sparselu],
              AS_HELP_STRING([--disable-sparselu], [Disable sparselu benchs]))
KASTORS_COMPILE_SPARSELU=no
AS_IF([test "x$enable_sparselu" != "xno"], [
KASTORS_COMPILE_SPARSELU=yes
     ])

dnl Add possibility to disable plasma
AC_ARG_ENABLE([plasma],
              AS_HELP_STRING([--disable-plasma], [Disable plasma benchs]))
KASTORS_COMPILE_PLASMA=no
AS_IF([test "x$enable_plasma" != "xno"], [
KASTORS_COMPILE_PLASMA=yes
     ])

dnl Check math support
AC_CHECK_LIB([m], [sqrt], [],
             [
                AC_MSG_ERROR([couldn't find sqrt in -lm])
dnl '
	     ]
)

dnl Check clock_gettime exist on unix systems
USE_LINUX="no"
case $host in
    *linux*)
      USE_LINUX="yes";;
esac

AS_IF([test "$USE_LINUX" == "yes"],
      [
       AC_CHECK_LIB([rt], [clock_gettime],
                    [],
                    [
                     AC_MSG_ERROR([couldn't find clock_gettime in -lrt.])
                     dnl '
                     KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS -lrt"
                     ]
                    )
       ])

dnl Add possibility to choose blas
AC_ARG_WITH([blas-installdir],
            [AS_HELP_STRING([--with-blas-installdir],
                            [specify include flags for blas(def=none)])],
            [],
            [with_blas_installdir=none])

dnl Add possibility to choose lapacke
AC_ARG_WITH([lapacke-installdir],
            [AS_HELP_STRING([--with-lapacke-installdir],
                            [specify include flags for lapacke(def=none)])],
            [],
            [with_lapacke_installdir=none])

I_PLASMA=
LD_PLASMA=
AS_IF( [test "x$with_blas_installdir" != "xnone" ],
      [
       I_PLASMA="$I_PLASMA -I$with_blas_installdir/include"
       LD_PLASMA="$LD_PLASMA -L$with_blas_installdir/lib"
       AC_MSG_CHECKING([for blas directory])
       AC_MSG_RESULT([-I$with_blas_installdir])
       ],
      [])

AS_IF( [test "x$with_lapacke_installdir" != "xnone" ],
      [
       I_PLASMA="$I_PLASMA -I$with_lapacke_installdir/include"
       LD_PLASMA="$LD_PLASMA -L$with_lapacke_installdir/lib"
       AC_MSG_CHECKING([for lapacke directory])
       AC_MSG_RESULT([-I$with_lapacke_installdir])
       ],
      [])

AC_ARG_WITH([mkl],
            [AS_HELP_STRING([--with-mkl],
                            [use Intel MKL BLAS and LAPACKE (def=no)])],
            [
              AS_IF( [test "x$CC" == "xicc" ], [CFLAGS="$CFLAGS -mkl=sequential"], [] )
              with_blas=mkl
              with_lapacke=mkl
             ],
            [with_mkl=no])

AC_SUBST([I_PLASMA], ["$I_PLASMA"])
AC_SUBST([LD_PLASMA], ["$LD_PLASMA"])

PLASMA_comLIBS=
dnl Check blas availability

dnl Add possibility to choose blas
AC_ARG_WITH([blas],
            [AS_HELP_STRING([--with-blas],
                            [specify blas you want to use(def=no)])],
            [],
            [with_blas=no])

dnl Add possibility to choose lapacke
AC_ARG_WITH([lapacke],
            [AS_HELP_STRING([--with-lapacke],
                            [specify lapacke library(def=lapacke)])],
            [],
            [with_lapacke=lapacke])


saved_LIBS=$LIBS
saved_LDFLAGS=$LDFLAGS
saved_CPPFLAGS=$CPPFLAGS
LDFLAGS="$LDFLAGS $LD_PLASMA"
CPPFLAGS="$CPPFLAGS $I_PLASMA"

AS_CASE([$with_blas],
      [no],
          [
           AC_MSG_WARN([No blas library are provided, please look at README for more information.])
           KASTORS_COMPILE_PLASMA=no
          ],
      [atlas],
          [
           PLASMA_comLIBS="$PLASMA_comLIBS -lcblas -llapack -latlas"
           AC_CHECK_HEADER([cblas.h], [],
                           [
                            AC_MSG_WARN([couldn't find cblas header. Deactivating compilation of the PLASMA benchmarks.])
dnl '
                            KASTORS_COMPILE_PLASMA=no
                            KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS cblas.h"
                            ])
           AC_CHECK_LIB([atlas], [ATL_dgemm],
                        [],
                        [
                         AC_MSG_WARN([couldn't find ATL_dgemm in -latlas. Deactivating compilation of the PLASMA benchmarks.])
                         dnl '
                         KASTORS_COMPILE_PLASMA=no
                         KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS -latlas"
                         ])
           AC_CHECK_LIB([lapack], [dlacpy_],
                        [],
                        [
                         AC_MSG_WARN([couldn't find dlacpy_ in -llapack. Deactivating compilation of the PLASMA benchmarks.])
                         dnl '
                         KASTORS_COMPILE_PLASMA=no
                         KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS -llapack"
                         ])
           AC_CHECK_LIB([cblas], [cblas_dgemm],
                        [],
                        [
                         AC_MSG_WARN([couldn't find cblas_dgemm in -lcblas. Deactivating compilation of the PLASMA benchmarks.])
                         dnl '
                         KASTORS_COMPILE_PLASMA=no
                         KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS -lcblas"
                         ])
          ],
      [openblas],
          [
           PLASMA_comLIBS="$PLASMA_comLIBS -lopenblas"
           AC_CHECK_HEADER([cblas.h], [],
                           [
                            AC_MSG_WARN([couldn't find cblas header. Deactivating compilation of the PLASMA benchmarks.])
dnl '
                            KASTORS_COMPILE_PLASMA=no
                            KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS cblas.h"
                            ])
           AC_CHECK_LIB([openblas], [cblas_dgemm],
                        [],
                         [
                          AC_MSG_WARN([couldn't find cblas_dgemm in -lopenblas. Deactivating compilation of the PLASMA benchmarks.])
                          dnl '
                          KASTORS_COMPILE_PLASMA=no
                          KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS -lopenblas"
                          ])
          ],
      [mkl],
          [
           PLASMA_comLIBS="$PLASMA_comLIBS $BLAS_LIB"
           AC_CHECK_HEADER([mkl_cblas.h], [],
                           [
                            AC_MSG_WARN([couldn't find mkl_cblas header. Deactivating compilation of the PLASMA benchmarks.])
dnl '
                            KASTORS_COMPILE_PLASMA=no
                            KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS mkl_cblas.h"
                            ])
          ],
      [
       PLASMA_comLIBS="$PLASMA_comLIBS $with_blas"
       AC_CHECK_HEADER([cblas.h], [],
                       [
                        AC_MSG_WARN([couldn't find cblas header. Deactivating compilation of the PLASMA benchmarks.])
                        dnl '
                        KASTORS_COMPILE_PLASMA=no
                        KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS cblas.h"
                        ])
      ])

AC_MSG_CHECKING([for blas])
AC_MSG_RESULT([$with_blas])

AS_IF([test "x$with_lapacke" != "xmkl" ],
      [
       AC_CHECK_HEADER([lapacke.h], [],
                       [
                        AC_MSG_WARN([couldn't find lapacke header. Deactivating compilation of the PLASMA benchmarks.])
                        dnl '
                        KASTORS_COMPILE_PLASMA=no
                        KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS lapacke.h"
                        ])
       ],
       [
        PLASMA_comLIBS="$LAPACK_LIB $PLASMA_comLIBS"
        AC_CHECK_HEADER([mkl_lapacke.h],
                        [
                         AC_DEFINE(USE_MKL, 1, [use MKL])
                         ],
                         [
                          AC_MSG_WARN([couldn't find mkl_lapacke header. Deactivating compilation of the PLASMA benchmarks.])
                          dnl '
                          KASTORS_COMPILE_PLASMA=no
                          KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS mkl_lapacke.h"
                          ])
        ])

AS_CASE([$with_lapacke],
        [lapacke],
        [
         PLASMA_comLIBS="-llapacke $PLASMA_comLIBS"
         AC_CHECK_LIB([lapacke], [LAPACKE_dlacpy_work],
                      [], [
                       AC_MSG_WARN([couldn't find LAPACKE_dlacpy_work in -llapacke. Deactivating compilation of the PLASMA benchmarks.])
                       dnl '
                       KASTORS_COMPILE_PLASMA=no
                       KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS -llapacke"
                       ])
         ],
         [openblas],
         [
          PLASMA_comLIBS="-lopenblas $PLASMA_comLIBS"
          AC_CHECK_LIB([openblas], [LAPACKE_dlacpy_work],
                       [], [
                        AC_MSG_WARN([couldn't find LAPACKE_dlacpy_work in -lopenblas. Deactivating compilation of the PLASMA benchmarks.])
                        dnl '
                        KASTORS_COMPILE_PLASMA=no
                        KASTORS_MISSING_DEPS="$KASTORS_MISSING_DEPS -lopenblas"
                        ])
          ],
          [mkl], [
           ],
           [
            PLASMA_comLIBS="$with_lapacke $PLASMA_comLIBS"
            ])

AC_MSG_CHECKING([for lapacke])
AC_MSG_RESULT([$with_lapacke])

LDFLAGS=$saved_LDFLAGS
CPPFLAGS=$saved_CPPFLAGS
LIBS=$saved_LIBS

AC_SUBST([PLASMA_comLIBS], ["$PLASMA_comLIBS"])

AM_CONDITIONAL([COMPILE_JACOBI],[test "$KASTORS_COMPILE_JACOBI" != "no"])
AM_CONDITIONAL([COMPILE_STRASSEN],[test "$KASTORS_COMPILE_STRASSEN" != "no"])
AM_CONDITIONAL([COMPILE_SPARSELU],[test "$KASTORS_COMPILE_SPARSELU" != "no"])
AM_CONDITIONAL([COMPILE_PLASMA],[test "$KASTORS_COMPILE_PLASMA" != "no"])

echo -e ""
echo -e "===== KaStORS configuration summary ====="
echo -e "Compiler: ""$CC"
echo -e "Flags:    ""$CFLAGS"
echo -e "\twill compile JACOBI?\t$KASTORS_COMPILE_JACOBI"
echo -e "\twill compile STRASSEN?\t$KASTORS_COMPILE_STRASSEN"
echo -e "\twill compile SPARSELU?\t$KASTORS_COMPILE_SPARSELU"
echo -e "\twill compile PLASMA?\t$KASTORS_COMPILE_PLASMA"
echo "========================================="

AC_CONFIG_FILES([
 Makefile
 strassen/Makefile
 jacobi/Makefile
 sparselu/Makefile
 plasma/Makefile
])
AC_OUTPUT

