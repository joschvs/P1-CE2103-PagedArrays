cmake_minimum_required(VERSION 3.10)
project(P1_CE2103_PagedArrays)

set(CMAKE_CXX_STANDARD 20)

add_executable(generator generator/main.cpp)

add_executable(sorter sorter/main.cpp
        sorter/BubbleSort.h
)