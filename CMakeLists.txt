cmake_minimum_required(VERSION 3.23)
project(aoc2022)

set(CMAKE_CXX_STANDARD 17)

add_executable(aoc2022 main.cpp InputLoader.cpp Runner.cpp Utils.cpp)
