cmake_minimum_required(VERSION 2.6)

# Project name

project(Serialize)

# Compilation flags

set(CMAKE_CXX_FLAGS "-std=c++0x")

# Set sources from all .cpp files in sources/ folder.

file(GLOB_RECURSE SOURCES example/*.cpp)

# Add includes

include_directories(.)

# Add sources

add_executable(test_serialize ${SOURCES})
