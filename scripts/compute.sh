#!/bin/bash

cd ../executables
echo "Compiling all files"
make
cd ../scripts
./openmp_block.sh
./openmp_diagonal.sh
./pthread_block.sh
./pthread_diagonal.sh


