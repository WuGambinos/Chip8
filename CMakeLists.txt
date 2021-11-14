cmake_minimum_required(VERSION 3.15)
project(chip8)

#Requires at least version 3.0
find_package(raylib 3.0 QUIET)

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

#Requires C11 Standard
set(CMAKE_C_STANDARD 11)

#include directories
include_directories(include)

#Checks if OSX and links appropiate frameworks (only required for MacOS)
if (APPLE)


    add_executable(mainMac src/main.c src/emu.c src/instruction.c src/disassemble.c include/raylib.h)

    target_link_libraries(mainMac raylib)
    target_link_libraries(mainMac "-framework IOKit")
    target_link_libraries(mainMac "-framework Cocoa")
    target_link_libraries(mainMac "-framework OpenGL")

#Check for Windows OS
elseif(WIN32)
    add_executable(mainWin src/main.c src/emu.c src/instruction.c src/disassemble.c include/raylib.h)
    target_link_libraries(mainWin raylib)

#Check for Linux
elseif(UNIX AND NOT APPLE)
    add_executable(mainLinux src/main.c src/emu.c src/instruction.c src/disassemble.c include/raylib.h)
    target_link_libraries(mainLinux raylib)
    target_link_libraries(mainLinux GL)
    target_link_libraries(mainLinux m)
    target_link_libraries(mainLinux pthread)
    target_link_libraries(mainLinux dl)
    target_link_libraries(mainLinux rt)
    target_link_libraries(mainLinux X11)

endif()
