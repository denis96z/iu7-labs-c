cmake_minimum_required(VERSION 3.9)
project(lab11 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab11
	main.c declarations.h
	graph_operations.h graph_operations.c)
