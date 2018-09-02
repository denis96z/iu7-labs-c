cmake_minimum_required(VERSION 3.9)
project(lab10 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab10
	main.c declarations.h
	io_unit.h io_unit.c
	str_utils.h str_utils.c
	task_solution.h task_solution.c)
