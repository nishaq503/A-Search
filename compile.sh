#!/usr/bin/env bash

# halt on first error
set -e

# remove current object files
rm -f *.o

# variables
compiler=g++
FLAGS="-Wall -Wextra -Wfatal-errors -pedantic"
INPUTS="main.cc Board/Board.cc"
output="main.o"

# compile
$compiler -g -std=c++11 $FLAGS $INPUTS -o $output

# Done
