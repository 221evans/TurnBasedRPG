cmake_minimum_required(VERSION 3.25)
project(TurnBasedRPG)



set(CMAKE_CXX_STANDARD 20)  # Use at least C++20 for modern features.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate SDL3 library
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

# Add your executable
add_executable(TurnBasedRPG main.cpp
        Core/Player.cpp
        Core/Player.h
        Core/Boar.cpp
        Core/Boar.h
        Core/AnimationData.h
        Core/GameState.h
        Core/Game.cpp
        Core/Game.h
)

# Link SDL3 and SDL3_image (no OpenGL needed for SDL renderer)
target_link_libraries(TurnBasedRPG PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# If needed, include SDL3 and SDL3_image headers
target_include_directories(TurnBasedRPG PRIVATE ${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})

# Include ImGui library
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/imgui)
set(IMGUI_SRC_FILES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp  # Use SDL renderer backend
)

# Add all ImGui sources to the build.
target_sources(TurnBasedRPG PRIVATE ${IMGUI_SRC_FILES})

# Include the backends and main ImGui directory.
target_include_directories(TurnBasedRPG PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Add debug symbols during compilation.
add_compile_options(-g -Wall)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(TurnBasedRPG PRIVATE DEBUG_BUILD)
endif()
