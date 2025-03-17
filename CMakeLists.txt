cmake_minimum_required(VERSION 3.10) 
# Set the project name and version 
set(PROJECT launchkey-tools)
project(${PROJECT} VERSION 1.0) 
# Specify the C standard 
set(CMAKE_C_STANDARD 99) 
set(CMAKE_C_STANDARD_REQUIRED True) 



file(GLOB_RECURSE LIB "src/lib/*.c")
file(GLOB_RECURSE INCONTROL_INIT_SOURCES "src/incontrol-init/*.c")
file(GLOB_RECURSE SEQUENCER_SOURCES "src/sequencer/*.c")

# Add an executable 
add_executable(incontrol-init ${LIB} ${INCONTROL_INIT_SOURCES})
add_executable(incontrol-sequencer ${LIB} ${SEQUENCER_SOURCES})

target_link_libraries(incontrol-init PRIVATE asound)
target_link_libraries(incontrol-sequencer PRIVATE asound)
target_include_directories(incontrol-init PRIVATE "src/lib")
target_include_directories(incontrol-sequencer PRIVATE "src/lib")
