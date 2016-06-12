cmake_minimum_required(VERSION 3.5)
project(heaps)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_subdirectory(lib/googletest)

add_library(heaps_lib  heap/BinHeap.cpp heap/BinHeap.h heap/util.h heap/RadixHeap.cpp heap/RadixHeap.h heap/ExtendedRadixHeap.cpp heap/ExtendedRadixHeap.h)

add_executable(heaps_main main.cpp)
target_link_libraries(heaps_main heaps_lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(heap)

add_executable(heaps_test test/test.cpp test/test_util.h test/test_util.cpp)
target_link_libraries(heaps_test gtest gtest_main)
target_link_libraries(heaps_test heaps_lib)

add_executable(heaps_perf test/perf_test.cpp test/Timer.cpp test/Timer.h test/test_util.h test/test_util.cpp)
target_link_libraries(heaps_perf heaps_lib)