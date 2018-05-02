#!/usr/bin/env bash

# halt on first error
set -e

# variables
compiler=g++
FLAGS="-Wall -Wextra -Wfatal-errors -pedantic"
INPUTS="main.cc board.cc"
output="main.o"

# remove current object files
rm -f *.o

# compile
$compiler -g -std=c++11 $FLAGS $INPUTS -o $output

# Done
