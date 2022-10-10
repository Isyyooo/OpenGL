cmake_minimum_required(VERSION 3.2)

project(LearnOpenGL)

include_directories(include)

link_libraries(-lglfw -lglad)

add_executable(demo main.cpp)
