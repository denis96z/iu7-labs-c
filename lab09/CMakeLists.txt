cmake_minimum_required(VERSION 3.9)
project(lab09 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab09
	main.c declarations.h
	io_unit.h io_unit.c
	tree_operations.h tree_operations.c)
