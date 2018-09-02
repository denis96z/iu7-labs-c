cmake_minimum_required(VERSION 3.9)
project(lab08 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab08
	main.c declarations.h
	task_solution.h task_solution.c
	stack_utils.h stack_utils.c
	queue_utils.h queue_utils.c)
