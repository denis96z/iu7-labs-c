cmake_minimum_required(VERSION 3.9)
project(lab02 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab02
	main.c
	declarations.h declarations.c
	functions.h functions.c
	integral_calculation.h integral_calculation.c
	roots_search.h roots_search.c)
