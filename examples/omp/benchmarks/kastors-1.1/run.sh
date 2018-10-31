#!/bin/sh

echo "$*" | grep "-help" >/dev/null 2>&1

if [ "$?" -eq "0" ]
then
    echo "
Usage : $0 [ OPTIONS ]
-------------------------------------------------------------------------------
 -t : num threads.
  Default is max num threads.
 -c : check (Default: false)
  Check if result is correct.
 -r : repeat.
  Number of repetition.
  Default : 1
 -rt : task repeat.
  Number of repetition for task run
  If not specify, default to repeat.
 -rtd : taskdep repeat.
  Number of repetition for taskdep run.
  If not specify, default to repeat.
 -rs : sequential repeate
  Number of repeatition for sequetial run.
  If not specify, default to repeat.
 -mode : benchmarks mode (Default: seq task taskdep)
  possible modes are task, taskdep and seq. If it doesn't exists, it will be
  ignored.
 -bench : bench to run (Default: strassen jacobi sparselu dgetrf dpotrf dgeqrf)
  Possible benchs are : strassen jacobi sparselu dgetrf dpotrf dgeqrf.
 -build_dir : Directory where build happened.
  Need to be specify if multiple build dir exists
Strassen
--------
 -n_strassen : matrix size (Default: 4096)
  Matrix size for strassen benchmark.
 -cutoff_size : limited size for strassen algorithm (Default: 64)
  When matrix is smaller than this size, standard algorithm is applied.
 -cutoff_depth : limited depth for parallelism (Default: 5)
  Only use OpenMP for 'cutoff_depth' first recursive calls.
SparseLU
--------
 -n_sparselu : matrix size (Default: 128)
  Matrix size for SparseLU benchmark.
 -m_sparselu : sub matrix size (Default: 64)
  Sub matrix size for SparseLU benchmark.
Jacobi
------
 -n_jacobi : matrix size (Default: 8192)
  Matrix size for Jacobi benchmark.
 -b_jacobi : bloc size (Default: 128)
  Bloc size for jacobi benchmark.
 -nbiter : iteration number (Default: 4)
  Number of iteration for Jacobi benchmark.
Dgetrf
------
 -n_dgetrf : matrix size (Default: 8192)
  Matrix size for dgetrf benchmark.
 -b_dgetrf : bloc size (Default: 224)
  Bloc size for dgetrf benchmark.
Dgeqrf
------
 -n_dgeqrf : matrix size (Default: 8192)
  Matrix size for dgeqrf benchmark.
  -b_dgeqrf : bloc size (Default: 224)
  Bloc size for dgeqrf benchmark.
Dpotrf
------
 -n_dpotrf : matrix size (Default: 8192)
  Matrix size for dpotrf benchmark.
 -b_dpotrf : bloc size (Default: 224)
  Bloc size for dpotrf benchmark."
  exit
fi

parse()
{
case $1 in
  "-t")
    threads=$2;
    shift 2;;
  "-r")
    repeat=$2;
    shift 2;;
  "-rt")
    repeat_task=$2;
    shift 2;;
  "-rtd")
    repeat_taskdep=$2;
    shift 2;;
  "-rs")
    repeat_seq=$2;
    shift 2;;
  "-c")
    check=true;
    shift;;
  "-n_strassen")
    n_strassen=$2;
    shift 2;;
  "-cutoff_size")
    cutoff_size=$2;
    shift 2;;
  "-cutoff_depth")
    cutoff_depth=$2;
    shift 2;;
  "-n_sparselu")
    n_sparselu=$2;
    shift 2;;
  "-m_sparselu")
    m_sparselu=$2;
    shift 2;;
  "-n_jacobi")
    n_jacobi=$2;
    shift 2;;
  "-b_jacobi")
    b_jacobi=$2;
    shift 2;;
  "-nbiter")
    nbiter=$2;
    shift 2;;
  "-n_dgetrf")
    n_dgetrf=$2;
    shift 2;;
  "-b_dgetrf")
    b_dgetrf=$2;
    shift 2;;
  "-n_dgeqrf")
    n_dgeqrf=$2;
    shift 2;;
  "-b_dgeqrf")
    b_dgeqrf=$2;
    shift 2;;
  "-n_dpotrf")
    n_dpotrf=$2;
    shift 2;;
  "-b_dpotrf")
    b_dpotrf=$2;
    shift 2;;
  "-mode")
    modes="$modes $2";
    shift 2;;
  "-bench")
    bench_names="$bench_names $2";
    shift 2;;
  "-build_dir")
    build_dir=$2;
    shift 2;;
  *)
    echo "unknown parameter : $1";
    shift 1;;
esac
if [ $# -gt 0 ]
then
  parse $*;
fi
}

# default values
threads=-1
check=false
repeat_task=-1
repeat_taskdep=-1
repeat_seq=-1
repeat=1
bench_names=""
modes=""
build_dir="."

n_strassen=4096
cutoff_depth=5
cutoff_size=64
n_sparselu=128
m_sparselu=64
n_jacobi=8192
b_jacobi=128
nbiter=4
n_dgetrf=8192
b_dgetrf=224
n_dgeqrf=8192
b_dgeqrf=224
n_dpotrf=8192
b_dpotrf=224

if [ $# -gt 1 ]
then
  parse $*;
fi

if [ ! "$bench_names" ]
then
  bench_names="strassen jacobi sparselu dpotrf dgetrf dgeqrf";
fi

if [ ! "$modes" ]
then
  modes="seq task taskdep";
fi

# specific repeat default to $repeat
for mode in $modes;
do
  v_name="repeat_${mode}"
  eval v_value=\${$v_name}
  if [ $v_value -lt 0 ]
  then
    eval $v_name=\$repeat;
  fi
done

if [ $threads -gt 0 ]
then
  export OMP_NUM_THREADS=$threads;
fi

strassen_args="-n $n_strassen -d $cutoff_depth -s $cutoff_size"
sparselu_args="-n $n_sparselu -m $m_sparselu"
jacobi_args="-n $n_jacobi -b $b_jacobi -r $nbiter"
dgetrf_args="-n $n_dgetrf -b $b_dgetrf"
dpotrf_args="-n $n_dpotrf -b $b_dpotrf"
dgeqrf_args="-n $n_dgeqrf -b $b_dgeqrf"

for bench_name in $bench_names;
do
  for mode in $modes;
  do
    v_name="repeat_${mode}"
    eval v_value=\${$v_name}
    cmd_line=`find $build_dir -name ${bench_name}_${mode}`
    if [ "x${v_value}" != "x0" ]
    then
      if [ $cmd_line ]
        then
          if $check
          then
            cmd_line="$cmd_line -c";
          fi
        eval value=\${${bench_name}_args}
        cmd_line="$cmd_line $value -i ${v_value}";
        eval $cmd_line 
      fi;
    fi;
  done;
done
