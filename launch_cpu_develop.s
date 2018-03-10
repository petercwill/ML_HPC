#!/bin/bash

#SBATCH --job-name=lab1
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=10GB
#SBATCH --time=00:20:00
#SBATCH --partition=c32_41
#SBATCH --output=out.%j

#Uncomment to execute C code
module load intel/17.0.1
./lab1

#Uncomment to execute python code
module purge
module load numpy/intel/1.13.1
python ./lab1.py

#Uncomment to execute pytorch code
#module load pytorch/python3.6/0.3.0_4
#python ./lab1.pytorch

