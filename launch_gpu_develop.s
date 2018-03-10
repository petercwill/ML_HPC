#!/bin/bash

#SBATCH --job-name=lab1
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=10GB
#SBATCH --gres=gpu
#SBATCH --time=01:00:00
#SBATCH --output=out.%j

module load pytorch/python3.6/0.3.0_4
python ./lab1.pytorch

