cmake_minimum_required(VERSION 3.9)
project(lab01 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab01
	main.c
	declarations.h
	io_utils.h io_utils.c
	string_utils.h string_utils.c)
