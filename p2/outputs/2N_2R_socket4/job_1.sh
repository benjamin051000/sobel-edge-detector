#!/bin/bash
#SBATCH --job-name=lab4
#SBATCH --mail-type=FAIL
#SBATCH --mail-user=stefenlagos@ufl.edu
#SBATCH --account=eel6763
#SBATCH --qos=eel6763
#SBATCH --nodes=2
#SBATCH --ntasks=4
#SBATCH --ntasks-per-node=2
#SBATCH --ntasks-per-socket=4
#SBATCH --cpus-per-task=4
#SBATCH --mem-per-cpu=600mb
#SBATCH -t 00:03:00
#SBATCH -o outlog
#SBATCH -e errorlog
export OMP_NUM_THREADS=4
srun --mpi=pmix_v3 ./build/sobel_edge_detector