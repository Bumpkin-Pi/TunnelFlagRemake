cmake_minimum_required(VERSION 3.27.8)
project(TunnelFlagRemake)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
if (WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
    set(SDL2_PATH "YOURSDL2DIRECTORYHERE/x86_64-w64-mingw32")
    set(SDL2_IMAGE_PATH "YOURSDL2_IMAGEDIRECTORYHERE/x86_64-w64-mingw32")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
else()
    find_package(SDL2 REQUIRED)
    set(SDL2_IMAGE_LIBRARIES "/lib/libSDL2_image.so") # I dont know why cmake is incapable of finding SDL2_image on its own, but at this point I'm too fed up to bother trying to find out.
    set(SDL2_NET_LIBRARIES "/lib/libSDL2_net.so")
endif()
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_subdirectory(Client)
add_subdirectory(Server)