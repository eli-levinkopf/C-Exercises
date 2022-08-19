cmake_minimum_required(VERSION 3.20)
project(ex1_eli_levinkopf C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex1_eli_levinkopf
        cipher.h
        ex1.c
        #        tests.c
        )