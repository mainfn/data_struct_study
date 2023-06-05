cmake_minimum_required(VERSION 3.25)
project(doha C)

set(CMAKE_C_STANDARD 11)

add_executable(doha main.c src/singly_linked_list.c)
