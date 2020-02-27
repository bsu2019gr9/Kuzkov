#!/bin/bash

# Remove obj files
rm *.o

# Compile
g++ -c lib/*.cpp
g++ -c $1

# Link
g++ *.o -o main

# Run
./main