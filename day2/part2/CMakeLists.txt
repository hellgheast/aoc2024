cmake_minimum_required(VERSION 3.2)
set(CXX_STANDARD 20)
project(aoc2024)
add_executable(aoc_day2_part2 src/main.cpp)

target_compile_options(aoc_day2 PUBLIC -Wall -Wextra -Wpedantic -Weffc++ -Wconversion -Wsign-conversion)