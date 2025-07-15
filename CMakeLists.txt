cmake_minimum_required(VERSION 3.25)
project(TurnBasedRPG)

set(CMAKE_CXX_STANDARD 26)

# Locate SDL3 library
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

# Add your executable
add_executable(TurnBasedRPG main.cpp
        Core/Player.cpp
        Core/Player.h
        Core/Boar.cpp
        Core/Boar.h
)

# Locate OpenGL
find_package(OpenGL REQUIRED)

# Link SDL3, SDL3_image, and OpenGL
target_link_libraries(TurnBasedRPG PRIVATE SDL3::SDL3 SDL3_image::SDL3_image OpenGL::GL)

# If needed, include SDL3 and SDL3_image headers
target_include_directories(TurnBasedRPG PRIVATE ${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})

# Include ImGui library
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/imgui)
set(IMGUI_SRC_FILES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Add ImGui sources to the executable
target_sources(TurnBasedRPG PRIVATE ${IMGUI_SRC_FILES})

# Include directories for ImGui
target_include_directories(TurnBasedRPG PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)