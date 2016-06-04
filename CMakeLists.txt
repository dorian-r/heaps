cmake_minimum_required(VERSION 3.5)
project(heaps)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp heap/BinHeap.cpp heap/BinHeap.h heap/util.h heap/RadixHeap.cpp heap/RadixHeap.h heap/ExtendedRadixHeap.cpp heap/ExtendedRadixHeap.h)
add_executable(heaps ${SOURCE_FILES})