cmake_minimum_required(VERSION 3.28)
project(TunnelFlagRemake)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src)

# Set the source files
set(SOURCE_FILES
        src/main.cpp
        src/keyboard.cpp
        src/keyboard.h
        src/renderer.cpp
        src/renderer.h
)

# Add the executable and link with SDL2 library
add_executable(TunnelFlagRemake ${SOURCE_FILES})
target_link_libraries(TunnelFlagRemake ${SDL2_LIBRARIES})
