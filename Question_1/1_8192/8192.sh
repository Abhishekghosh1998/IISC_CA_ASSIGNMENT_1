#!/bin/sh
#SBATCH --job-name=8192
#SBATCH --ntasks=1
#SBATCH --time=72:00:00
#SBATCH --output=8192.out
#SBATCH --partition=low_unl_1gpu
#SBATCH --mem=32GB
#SBATCH --mail-type=END
#SBATCH --mail-user=abhishekghos@iisc.ac.in

./8192_i_j_k 8	> stat_8192_8_i_j_k.log
./8192_i_j_k 16	> stat_8192_16_i_j_k.log
./8192_i_j_k 32	> stat_8192_32_i_j_k.log
./8192_i_j_k 64	> stat_8192_64_i_j_k.log
./8192_i_j_k 128	> stat_8192_128_i_j_k.log
./8192_i_j_k 256	> stat_8192_256_i_j_k.log
./8192_i_j_k 512	> stat_8192_512_i_j_k.log
./8192_i_j_k 1024	> stat_8192_1024_i_j_k.log
./8192_i_j_k 2048	> stat_8192_2048_i_j_k.log
./8192_i_j_k 4096	> stat_8192_4096_i_j_k.log
./8192_i_j_k 8192	> stat_8192_8192_i_j_k.log

./8192_i_k_j 8	> stat_8192_8_i_k_j.log
./8192_i_k_j 16	> stat_8192_16_i_k_j.log
./8192_i_k_j 32	> stat_8192_32_i_k_j.log
./8192_i_k_j 64	> stat_8192_64_i_k_j.log
./8192_i_k_j 128	> stat_8192_128_i_k_j.log
./8192_i_k_j 256	> stat_8192_256_i_k_j.log
./8192_i_k_j 512	> stat_8192_512_i_k_j.log
./8192_i_k_j 1024	> stat_8192_1024_i_k_j.log
./8192_i_k_j 2048	> stat_8192_2048_i_k_j.log
./8192_i_k_j 4096	> stat_8192_4096_i_k_j.log
./8192_i_k_j 8192	> stat_8192_8192_i_k_j.log

./8192_k_i_j 8	> stat_8192_8_k_i_j.log
./8192_k_i_j 16	> stat_8192_16_k_i_j.log
./8192_k_i_j 32	> stat_8192_32_k_i_j.log
./8192_k_i_j 64	> stat_8192_64_k_i_j.log
./8192_k_i_j 128	> stat_8192_128_k_i_j.log
./8192_k_i_j 256	> stat_8192_256_k_i_j.log
./8192_k_i_j 512	> stat_8192_512_k_i_j.log
./8192_k_i_j 1024	> stat_8192_1024_k_i_j.log
./8192_k_i_j 2048	> stat_8192_2048_k_i_j.log
./8192_k_i_j 4096	> stat_8192_4096_k_i_j.log
./8192_k_i_j 8192	> stat_8192_8192_k_i_j.log
