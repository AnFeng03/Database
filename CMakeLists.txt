cmake_minimum_required(VERSION 3.26)
project(Project4 C)

set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -pedantic)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(Project4
        main.c
        database.h
        database.c
        hashTable.c
        hashTable.h
)
