cmake_minimum_required(VERSION 3.20)
project(ex2_eli_levinkopf C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex2_eli_levinkopf
        ex2.c
        ex2.h
#        main.c
#        test.c
        test_ex2.c
#        strtok_example.c
#        a.c
        )
