#!/bin/bash

# This displays the real world time taken to execute
# the OpenMP implementation of the diagonal transposition method

# The results for both 1 and 4 threads, for a variety of matrix 
# dimentions are computed.

# The real time is what was measured

# 128 x 128 matrix

echo ""

echo "Transposing a 128x128 matrix with OpenMP diagonal (1 thread):"
time ../executables/openmp_diagonal 1 128

echo ""

echo "Transposing a 128x128 matrix with OpenMP diagonal (4 threads):"
time ../executables/openmp_diagonal 4 128

# 1024 x 1024 matrix

echo ""

echo "Transposing a 1024x1024 matrix with OpenMP diagonal (1 thread):"
time ../executables/openmp_diagonal 1 1024

echo ""

echo "Transposing a 1024x1024 matrix with OpenMP diagonal (4 threads):"
time ../executables/openmp_diagonal 1 1024

# 2048 x 2048 matrix

echo ""

echo "Transposing a 2048x2048 matrix with OpenMP diagonal (1 thread):"
time ../executables/openmp_diagonal 1 2048

echo ""

echo "Transposing a 2048x2048 matrix with OpenMP diagonal (4 threads):"
time ../executables/openmp_diagonal 4 2048

# 4096 x 4096 matrix

echo ""

echo "Transposing a 4096x4096 matrix with OpenMP diagonal (1 thread):"
time ../executables/openmp_diagonal 1 4096

echo ""

echo "Transposing a 4096x4096 matrix with OpenMP diagonal (4 threads):"
time ../executables/openmp_diagonal 4 4096
