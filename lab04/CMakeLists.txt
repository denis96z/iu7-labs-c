cmake_minimum_required(VERSION 3.9)
project(lab04 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab04
	main.c
	declarations.h
	utils.h utils.c
	xml_utils.h xml_utils.c
	table_utils.h table_utils.c)
