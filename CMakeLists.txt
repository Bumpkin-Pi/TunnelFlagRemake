cmake_minimum_required(VERSION 3.28)
project(TunnelFlagRemake)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2 package
if (WIN32)
    set(SDL2_PATH "path_to_your_SDL2_folder") # Set the path to your SDL2 folder on Windows
    set(SDL2_IMAGE_PATH "path_to_your_SDL2_image_folder") # Set the path to your SDL2_image folder on Windows
    find_package(SDL2 REQUIRED)
else()
    find_package(SDL2 REQUIRED)
    set(SDL2_IMAGE_LIBRARIES "/lib/libSDL2_image.so") # I dont know why cmake is incapable of finding SDL2_image on its own, but at this point I'm too fed up to bother trying to find out.
endif()

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Include SDL_image headers
if (WIN32)
    include_directories(${SDL2_IMAGE_PATH}/include)
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
)

# Add the executable and link with SDL2 and SDL_image libraries
add_executable(TunnelFlagRemake ${SOURCE_FILES})

set_target_properties(TunnelFlagRemake PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

if (WIN32)
    target_link_libraries(TunnelFlagRemake ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}/SDL2_image.lib)
else()
    target_link_libraries(TunnelFlagRemake ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()
