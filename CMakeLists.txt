cmake_minimum_required(VERSION 3.18)
# Set the project name and version
set(PROJECT launchkey-tools)
project(${PROJECT} VERSION 1.0)
# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)



file(GLOB_RECURSE LIB "src/core/*.c")
file(GLOB_RECURSE INCONTROL_INIT_SOURCES "src/incontrol-init/*.c")
file(GLOB_RECURSE SEQUENCER_SOURCES "src/sequencer/*.c")

# Add an executable
add_executable(incontrol-init ${LIB} ${INCONTROL_INIT_SOURCES})
add_executable(incontrol-sequencer ${LIB} ${SEQUENCER_SOURCES})
add_subdirectory(vendor/iniparser build)

add_dependencies(incontrol-init iniparser-static)

target_link_libraries(incontrol-init PRIVATE asound iniparser)
target_link_directories(incontrol-init PRIVATE build/vendor/iniparser)
target_include_directories(incontrol-init PRIVATE "src/core" "src" ${iniparser_PUBLIC_HEADERS})
target_link_libraries(incontrol-sequencer PRIVATE asound iniparser)
target_link_directories(incontrol-sequencer PRIVATE build/vendor/iniparser)
target_include_directories(incontrol-sequencer PRIVATE ${iniparser_PUBLIC_HEADERS} "src/core" "src")
