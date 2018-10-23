#!/bin/sh
#############################################################
#### Use 'qsub filename' to submit job                   ####
#### Follow the jobs progress with one of these commands ####
####      'qstat -a'                                     ####
####      'watch qstat -a'                               ####
#### Use 'qdel job-id' to cancel the job                 ####
#############################################################
#
### Job name
#PBS -N ex7
#
### Account name
#PBS -A ACCOUNT
#
# max. walltime (must not exceed max. walltime for queue)
#PBS -l walltime=00:01:00
#
### The number of nodes and processes per node
#PBS -lnodes=1:ppn=5
#
### Queue name
#PBS -q default
#
### Send us a mail when job starts execution, if it is aborted, and when it has finished
#PBS -m abe
##PBS -M <<e-mail address>>
#
#### Priority
#PBS -p 0
#
### Non rerunable
#PBS -r n
#
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

cd $PBS_O_WORKDIR

module load intelcomp
module load openmpi/1.4.3-intel

mpirun --app ./cmdfile.pbs -hostfile $PBS_NODEFILE
