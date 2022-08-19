cmake_minimum_required(VERSION 3.20)
project(ex3_eli_levinkopf C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

set(CMAKE_C_FLAGS "-Wextra -Werror -Wall -Wvla -std=c99")

add_executable(ex3_eli_levinkopf
        ex3.c
        ex3.h
        test_ex3.c
#        test_runner.h
#        test_runner.c
#        tests.c
        )
