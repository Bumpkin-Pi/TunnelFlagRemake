if (WIN32)
    include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} include)
else()
    include_directories(include)
endif()

# Set the source files
set(SOURCE_FILES
        src/main.cpp
)

# Add the executable and link with SDL2 and SDL_image libraries
add_executable(TunnelFlagRemakeServer ${SOURCE_FILES})
if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
else()
    target_link_libraries(TunnelFlagRemakeServer ${SDL2_LIBRARIES})
endif()

install(TARGETS TunnelFlagRemakeServer RUNTIME DESTINATION bin)
