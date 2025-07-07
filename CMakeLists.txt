cmake_minimum_required(VERSION 3.25)
project(TurnBasedRPG)

set(CMAKE_CXX_STANDARD 26)

# Locate SDL3 library
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

# Add your executable
add_executable(TurnBasedRPG main.cpp
        Core/Player.cpp
        Core/Player.h)

# Link SDL3 and SDL3_image libraries
target_link_libraries(TurnBasedRPG PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# If needed, include SDL3 and SDL3_image headers
target_include_directories(TurnBasedRPG PRIVATE ${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})