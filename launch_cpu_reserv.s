#!/bin/bash

#SBATCH --job-name=lab1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=20
#SBATCH --mem=62GB
#SBATCH --time=00:30:00
#SBATCH --res=morari 
#SBATCH --partition=c26
#SBATCH --exclusive
#SBATCH --output=out.%j

#Uncomment to execute C code
module load intel/17.0.1
./lab1

#Uncomment to execute python code
#module purge
#module load numpy/intel/1.13.1
#python ./lab1.py

#Uncomment to execute pytorch code
#module load pytorch/python3.6/0.3.0_4
#python ./lab1.pytorch

