cmake_minimum_required(VERSION 3.20)
project(GC_Arborescent C)

set(CMAKE_C_STANDARD 11)

add_executable(GC_Arborescent
        main.c
        gc.c
        bench.c
)