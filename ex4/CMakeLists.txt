cmake_minimum_required(VERSION 3.20)
project(ex4_eli_levinkopf C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex4_eli_levinkopf
        HashSet.h
        Node.h
        Node.c
        HashSet.c
#        testNode.c
#        presubmit.c
#        TestHashSet.c
        test_runner.c
        test_runner.h
        tests.c
#        Makefile
        )
