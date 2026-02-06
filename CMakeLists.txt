cmake_minimum_required(VERSION 3.20)
project(sdl3-tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find external dependencies
find_package(glm CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

enable_testing()

# Library
add_library(sdl3_engine
  # ${PROJECT_SOURCE_DIR}/src/engine/animation.cpp
  ${PROJECT_SOURCE_DIR}/src/engine/engine.cpp
  ${PROJECT_SOURCE_DIR}/src/engine/game_object.cpp
  # ${PROJECT_SOURCE_DIR}/src/engine/main_app.cpp
  # ${PROJECT_SOURCE_DIR}/src/engine/timer.cpp
  ${PROJECT_SOURCE_DIR}/src/engine/world.cpp

  ${PROJECT_SOURCE_DIR}/src/engine/subsystems/input_subsystem.cpp
)

target_include_directories(sdl3_engine
  PUBLIC
    ${PROJECT_SOURCE_DIR}/public
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# Link dependencies to engine
target_link_libraries(sdl3_engine PUBLIC glm::glm SDL3::SDL3 SDL3_image::SDL3_image)

# Executable
add_executable(sdl3_tutorial
  ${PROJECT_SOURCE_DIR}/src/main.cpp

  ${PROJECT_SOURCE_DIR}/src/game/player.cpp
)

target_include_directories(sdl3_tutorial
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(sdl3_tutorial PRIVATE sdl3_engine)

add_subdirectory(tests)
