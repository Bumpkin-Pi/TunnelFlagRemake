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
#    set(SDL2_NET_LIBRARIES "/lib/libSDL2_net.so")
endif()

# Include SDL2 headers

# Include SDL_image headers
if (WIN32)
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
endif()

# Set the source files
set(SOURCE_FILES
        src/main.cpp
        src/io/keyboard.cpp
        src/io/keyboard.h
        src/io/renderer.cpp
        src/io/renderer.h
        src/game/entity.cpp
        src/game/entity.h
        src/loadTextures.cpp
        src/loadTextures.h
        src/game/game.cpp
        src/game/game.h
        src/game/player.cpp
        src/game/player.h
        src/game/map.cpp
        src/game/map.h
)

# Add the executable and link with SDL2 and SDL_image libraries
add_executable(TunnelFlagRemake ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
else()
    target_link_libraries(TunnelFlagRemake ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()
