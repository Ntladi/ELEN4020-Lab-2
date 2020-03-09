#!/bin/bash

# This displays the real world time taken to execute
# the OpenMP implementation of the block transposition method

# The results for both 1 and 4 threads, as well as small and optimum
# block sizes for a variety of matrix dimentions are computed.
 
# This is to show that increasing the thread count AND the block size
# are important in order to achieve maximum performance.

# Furthermore, this is evident in how the worst case (Unoptimized block
# size and few threads) performs worse than the the best case (Optimized
# block size and many threads)

# The real time is what was measured

# 128 x 128 matrix

echo ""

echo "Transposing a 128x128 matrix with OpenMP block (1 thread and block size of 2):"
time ../executables/openmp_block 1 128 2

echo ""

echo "Transposing a 128x128 matrix with OpenMP block (4 thread and block size of 2):"
time ../executables/openmp_block 4 128 2

# 1024 x 1024 matrix

echo ""

echo "Transposing a 1024x1024 matrix with OpenMP block (1 thread and block size of 2):"
time ../executables/openmp_block 1 1024 2

echo ""

echo "Transposing a 1024x1024 matrix with OpenMP block (1 thread and block size of 8 [Optimal]):"
time ../executables/openmp_block 1 1024 8

echo ""

echo "Transposing a 1024x1024 matrix with OpenMP block (4 thread and block size of 2):"
time ../executables/openmp_block 4 1024 2

echo ""

echo "Transposing a 1024x1024 matrix with OpenMP block (4 thread and block size of 8 [Optimal]):"
time ../executables/openmp_block 4 1024 8

# 2048 x 2048 matrix

echo ""

echo "Transposing a 2048x2048 matrix with OpenMP block (1 thread and block size of 2):"
time ../executables/openmp_block 1 2048 2

echo ""

echo "Transposing a 2048x2048 matrix with OpenMP block (1 thread and block size of 8 [Optimal]):"
time ../executables/openmp_block 1 2048 8

echo ""

echo "Transposing a 2048x2048 matrix with OpenMP block (4 thread and block size of 2):"
time ../executables/openmp_block 4 2048 2

echo ""

echo "Transposing a 2048x2048 matrix with OpenMP block (4 thread and block size of 8 [Optimal]):"
time ../executables/openmp_block 4 2048 8

# 4096 x 4096 matrix

echo ""

echo "Transposing a 4096x4096 matrix with OpenMP block (1 thread and block size of 2):"
time ../executables/openmp_block 1 4096 2

echo ""

echo "Transposing a 4096x4096 matrix with OpenMP block (1 thread and block size of 16 [Optimal]):"
time ../executables/openmp_block 1 4096 16

echo ""

echo "Transposing a 4096x4096 matrix with OpenMP block (4 thread and block size of 2):"
time ../executables/openmp_block 4 4096 2

echo ""

echo "Transposing a 4096x4096 matrix with OpenMP block (4 thread and block size of 16 [Optimal]):"
time ../executables/openmp_block 4 4096 16
