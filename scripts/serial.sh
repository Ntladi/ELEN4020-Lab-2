#!/bin/bash

# This displays the real world time taken to execute
# the serial implementation of the naive transposition method

# The results for a variety of matrix dimentions are computed.

# The real time is what was measured

# 128 x 128 matrix

echo ""

echo "Transposing a 128x128 matrix with the serial method:"
time ../executables/serial 128

# 1024 x 1024 matrix

echo ""

echo "Transposing a 1024x1024 matrix with the serial method:"
time ../executables/serial 1024

# 2048 x 2048 matrix

echo ""

echo "Transposing a 2048x2048 matrix with the serial method:"
time ../executables/serial 2048

# 4096 x 4096 matrix

echo ""

echo "Transposing a 4096x4096 matrix with the serial method:"
time ../executables/serial 4096
