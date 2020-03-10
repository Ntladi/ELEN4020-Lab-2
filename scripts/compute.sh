#!/bin/bash

cd ../executables
echo "Compiling all files"
make
cd ../scripts
./openmp_naive.sh
./openmp_block.sh
./openmp_diagonal.sh
./pthread_block.sh
./pthread_diagonal.sh

