cmake_minimum_required(VERSION 3.9)
project(lab05 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab05
	main.c
	declarations.h
	io_unit.h io_unit.c
	analysis_unit.h analysis_unit.c)
