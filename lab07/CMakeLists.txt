cmake_minimum_required(VERSION 3.9)
project(lab07 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab07
	main.c declarations.h
	io_utils.h io_utils.c
	token_utils.h token_utils.c)
