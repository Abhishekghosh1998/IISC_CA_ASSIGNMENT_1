#!/bin/sh
#SBATCH --job-name=trace
#SBATCH --ntasks=1
#SBATCH --time=100:00:00
#SBATCH --output=trace.out
#SBATCH --partition=low_unl_1gpu
#SBATCH --mem=64GB
#SBATCH --mail-type=END
#SBATCH --mail-user=abhishekghos@iisc.ac.in



./dramsim3main ../custom_configs/CLOSE_CACHE_FCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/CLOSE_CACHE_FRFCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/CLOSE_ROW_FCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/CLOSE_ROW_FRFCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_4_CACHE_FCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_4_CACHE_FRFCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_4_ROW_FCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_4_ROW_FRFCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_CACHE_FCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_CACHE_FRFCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_ROW_FCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out
./dramsim3main ../custom_configs/OPEN_ROW_FRFCFS.ini -o bench1_outputs -c 280000000 -t ../tests/trace_bench_1.out

./dramsim3main ../custom_configs/CLOSE_CACHE_FCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/CLOSE_CACHE_FRFCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/CLOSE_ROW_FCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/CLOSE_ROW_FRFCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_4_CACHE_FCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_4_CACHE_FRFCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_4_ROW_FCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_4_ROW_FRFCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_CACHE_FCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_CACHE_FRFCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_ROW_FCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out
./dramsim3main ../custom_configs/OPEN_ROW_FRFCFS.ini -o bench2_outputs -c 280000000 -t ../tests/trace_bench_2.out

./dramsim3main ../custom_configs/CLOSE_CACHE_FCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/CLOSE_CACHE_FRFCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/CLOSE_ROW_FCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/CLOSE_ROW_FRFCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_4_CACHE_FCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_4_CACHE_FRFCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_4_ROW_FCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_4_ROW_FRFCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_CACHE_FCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_CACHE_FRFCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_ROW_FCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out
./dramsim3main ../custom_configs/OPEN_ROW_FRFCFS.ini -o bench3_outputs -c 280000000 -t ../tests/trace_bench_3.out

