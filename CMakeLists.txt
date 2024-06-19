cmake_minimum_required(VERSION 3.10)
project(openChess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Source files
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SRC})

# Linker flags
target_link_libraries(${PROJECT_NAME}
    glfw3
    GL
    X11
    pthread
    Xrandr
    Xi
    dl
    assimp
)
