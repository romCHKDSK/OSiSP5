cmake_minimum_required(VERSION 3.0)

project(lr5 LANGUAGES C)

add_executable(lr5 main.c)

install(TARGETS lr5 RUNTIME DESTINATION bin)
