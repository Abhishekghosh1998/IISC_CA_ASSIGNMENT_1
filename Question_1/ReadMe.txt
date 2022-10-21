-------------------------------------------------------------------------------------------------------------------
The files related to N=2048 are present under the directory named "1_2048"

The files which are present are:
	a. 2048_i_j_k.c
	b. 2048_i_k_j.c
	c. 2048_k_i_j.c

Build the following the using the following commands:

gcc 2048_i_j_k.c -o 2048_i_j_k	
gcc 2048_i_k_j.c -o 2048_i_k_j
gcc 2048_k_i_j.c -o 2048_k_i_j

Each of the executables generated takes only one command line argument, the tile size.
The output is shown on the stdout, but default. Use output redirection in linux to write it to a situitable file.

The directory 1_2048 contains a bash script named 2048.sh which shows how to call the executables.


--------------------------------------------------------------------------------------------------------------------

For the N=4096 the process is similar, as above.
