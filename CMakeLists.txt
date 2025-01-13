cmake_minimum_required(VERSION 3.10) 
# Set the project name and version 
set(PROJECT launchkey-tools)
project(${PROJECT} VERSION 1.0) 
# Specify the C standard 
set(CMAKE_C_STANDARD 99) 
set(CMAKE_C_STANDARD_REQUIRED True) 

file(GLOB_RECURSE SOURCES "src/*.c")

# Add an executable 
add_executable(${PROJECT} ${SOURCES})

target_link_libraries(${PROJECT} PRIVATE asound)
