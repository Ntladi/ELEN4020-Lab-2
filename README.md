# ELEN4020-Lab-2
## Matrix Transposition using parallel programming 
This lab is written in C and the code was run 5 times. The average results are what were documented in the report. 

## Compile Instructions
In order to emulate the results recorded in the lab report as close as possible, please note the following:

* The linux version is Ubuntu 18.04.4 LTS
* The compiler is gcc version 7.4.0
* GNU Make version 4.1 is used to compile the source code

In order to produce the results, clone the repository and run the **compute.sh** script in the **scripts** folder.
The script will compile all the source code located in the **src** folder.
Once compiled, the executable files can be found in the **executables** folder.
The MakeFile can also be found in the **executables** folder
Miscilanious scripts used to run the algorithm are found in the **scripts** folder.

In order to run and time each of the executables that use the block implementation, run the following command:

time ./{executable name} {number of threads} {matrix size} {block size}

_Example:_  time ./pthread_block 4 1024 8

In order to run and time each of the executables that use the diagonal implementation, run the following command:

time ./{executable name} {number of threads} {matrix size}

_Example:_  time ./openmp_diagonal 2 128

The results will be shown in the terminal window and the real time is what was recorded. 
