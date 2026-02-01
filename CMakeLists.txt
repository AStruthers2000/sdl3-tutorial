cmake_minimum_required(VERSION 3.20)
project(sdl3-tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find external dependencies
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

enable_testing()

# Library
add_library(sdl3_engine
  ${PROJECT_SOURCE_DIR}/public/engine/main_app.h
  ${PROJECT_SOURCE_DIR}/src/engine/main_app.cpp
)

target_include_directories(sdl3_engine
  PUBLIC
    ${PROJECT_SOURCE_DIR}/public
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# Link dependencies to engine
target_link_libraries(sdl3_engine PUBLIC SDL3::SDL3 SDL3_image::SDL3_image)

# Executable
add_executable(sdl3_tutorial
  ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(sdl3_tutorial
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(sdl3_tutorial PRIVATE sdl3_engine)

add_subdirectory(tests)
