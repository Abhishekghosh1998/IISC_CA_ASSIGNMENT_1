#!/bin/sh
#SBATCH --job-name=2048
#SBATCH --ntasks=1
#SBATCH --time=72:00:00
#SBATCH --output=2048.out
#SBATCH --partition=low_unl_1gpu
#SBATCH --mem=32GB
#SBATCH --mail-type=END
#SBATCH --mail-user=abhishekghos@iisc.ac.in

./2048_i_j_k 8	> stat_2048_8_i_j_k.log
./2048_i_j_k 16	> stat_2048_16_i_j_k.log
./2048_i_j_k 32	> stat_2048_32_i_j_k.log
./2048_i_j_k 64	> stat_2048_64_i_j_k.log
./2048_i_j_k 128	> stat_2048_128_i_j_k.log
./2048_i_j_k 256	> stat_2048_256_i_j_k.log
./2048_i_j_k 512	> stat_2048_512_i_j_k.log
./2048_i_j_k 1024	> stat_2048_1024_i_j_k.log
./2048_i_j_k 2048	> stat_2048_2048_i_j_k.log

./2048_i_k_j 8	> stat_2048_8_i_k_j.log
./2048_i_k_j 16	> stat_2048_16_i_k_j.log
./2048_i_k_j 32	> stat_2048_32_i_k_j.log
./2048_i_k_j 64	> stat_2048_64_i_k_j.log
./2048_i_k_j 128	> stat_2048_128_i_k_j.log
./2048_i_k_j 256	> stat_2048_256_i_k_j.log
./2048_i_k_j 512	> stat_2048_512_i_k_j.log
./2048_i_k_j 1024	> stat_2048_1024_i_k_j.log
./2048_i_k_j 2048	> stat_2048_2048_i_k_j.log

./2048_k_i_j 8	> stat_2048_8_k_i_j.log
./2048_k_i_j 16	> stat_2048_16_k_i_j.log
./2048_k_i_j 32	> stat_2048_32_k_i_j.log
./2048_k_i_j 64	> stat_2048_64_k_i_j.log
./2048_k_i_j 128	> stat_2048_128_k_i_j.log
./2048_k_i_j 256	> stat_2048_256_k_i_j.log
./2048_k_i_j 512	> stat_2048_512_k_i_j.log
./2048_k_i_j 1024	> stat_2048_1024_k_i_j.log
./2048_k_i_j 2048	> stat_2048_2048_k_i_j.log
