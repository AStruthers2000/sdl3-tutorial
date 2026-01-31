cmake_minimum_required(VERSION 3.20)
project(sdl3-tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Main executable
add_library(sdl3_engine
  ${PROJECT_SOURCE_DIR}/src/engine/main_app.cpp
)

target_include_directories(sdl3_engine
  PUBLIC
    ${PROJECT_SOURCE_DIR}/public
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

add_executable(sdl3_tutorial src/main.cpp)

target_include_directories(sdl3_tutorial
  PUBLIC
    ${PROJECT_SOURCE_DIR}/public
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_compile_features(sdl3_tutorial PRIVATE cxx_std_20)

target_link_libraries(sdl3_tutorial PRIVATE sdl3_engine)

if(TARGET CONAN_PKG::sdl)
  target_link_libraries(sdl3_engine PRIVATE CONAN_PKG::sdl)
  target_link_libraries(sdl3_tutorial PRIVATE CONAN_PKG::sdl)
else()
  find_package(SDL3 CONFIG REQUIRED)
  target_link_libraries(sdl3_engine PRIVATE SDL3::SDL3)
  target_link_libraries(sdl3_tutorial PRIVATE SDL3::SDL3)
endif()

add_subdirectory(tests)
