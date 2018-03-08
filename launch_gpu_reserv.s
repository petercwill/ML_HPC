#!/bin/bash

#SBATCH --job-name=lab1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=28
#SBATCH --mem=250GB
#SBATCH --gres=gpu:k80:4
#SBATCH --time=00:20:00
#SBATCH --res=morari 
#SBATCH --partition=k80_4
#SBATCH --exclusive
#SBATCH --output=out.%j

module load pytorch/python3.6/0.3.0_4
python ./lab1.pytorch
