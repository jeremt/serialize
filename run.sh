#!/bin/sh

# Simple script to build application using cmake, and run it on
# UNIX shell.

NAME=test_serialize

# Build program
mkdir -p build && cd build && cmake .. && make && cp ${NAME} .. &&

# Run program
cd .. && ./${NAME}