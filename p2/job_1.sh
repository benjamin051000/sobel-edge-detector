#!/bin/bash
#SBATCH --job-name=lab3_p2_hybrid
#SBATCH --mail-type=FAIL
#SBATCH --mail-user=stefenlagos@ufl.edu
#SBATCH --account=eel6763
#SBATCH --qos=eel6763
#SBATCH --nodes=8
#SBATCH --ntasks=8
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --mem-per-cpu=600mb
#SBATCH -t 00:03:00
#SBATCH -o Table2_Row4
#SBATCH -e errorlog
export OMP_NUM_THREADS=64
srun --mpi=pmix_v3 ./build/sobel_edge_detector