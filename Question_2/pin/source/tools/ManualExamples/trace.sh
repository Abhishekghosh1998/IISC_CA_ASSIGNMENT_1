#!/bin/sh
#SBATCH --job-name=trace
#SBATCH --ntasks=1
#SBATCH --time=72:00:00
#SBATCH --output=trace.out
#SBATCH --partition=low_unl_1gpu
#SBATCH --mem=32GB
#SBATCH --mail-type=END
#SBATCH --mail-user=abhishekghos@iisc.ac.in


../../../pin -t obj-intel64/trace_bench_1.so -- /data/home/abhishekghos/CA_ASSIGNMENTS/Microbenchmarks/bin/bench_1
../../../pin -t obj-intel64/trace_bench_2.so -- /data/home/abhishekghos/CA_ASSIGNMENTS/Microbenchmarks/bin/bench_2
../../../pin -t obj-intel64/trace_bench_3.so -- /data/home/abhishekghos/CA_ASSIGNMENTS/Microbenchmarks/bin/bench_3


