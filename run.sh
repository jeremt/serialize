#!/bin/sh

# Simple script to build application using cmake, and run it on
# UNIX shell.

# Program's name

NAME=test_serialize

# Build program

mkdir -p build && cd build && cmake .. && make &&

# Run program

./${NAME}