if (WIN32)
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} include)
else()
    include_directories(include)
endif()

# Set the source files
set(SOURCE_FILES
        src/main.cpp
        src/io/keyboard.cpp
        src/io/renderer.cpp
        src/game/entity.cpp
        src/loadTextures.cpp
        src/game/game.cpp
        src/game/player.cpp
        src/game/map.cpp
)

# Add the executable and link with SDL2 and SDL_image libraries
add_executable(TunnelFlagRemakeClient ${SOURCE_FILES})
if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
else()
    target_link_libraries(TunnelFlagRemakeClient ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()

install(TARGETS TunnelFlagRemakeClient RUNTIME DESTINATION bin)
