cmake_minimum_required(VERSION 3.15)
project(chip8)

#Requires at least version 3.0
find_package(raylib 3.0 REQUIRED) 

#Requires C11 Standard
set(CMAKE_C_STANDARD 11)

#include directories
include_directories(include)

add_executable(mainMac src/main.c src/emu.c src/instruction.c src/disassemble.c include/raylib.h)
target_link_libraries(mainMac raylib)

#Checks if OSX and links appropiate  frameworks (only required on MacOS)

if (APPLE)
    target_link_libraries(mainMac "-framework IOKit")
    target_link_libraries(mainMac "-framework Cocoa")
    target_link_libraries(mainMac "-framework OpenGL")

endif()
