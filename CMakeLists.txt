cmake_minimum_required(VERSION 3.20)
project(sdl3-tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# If Conan generated a toolchain file in the build dir, include it.
if(EXISTS ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
  message(STATUS "Including Conan toolchain: ${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
  include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
endif()

# Main executable
add_executable(sdl3_tutorial src/main.cpp)

target_compile_features(sdl3_tutorial PRIVATE cxx_std_20)

if(TARGET CONAN_PKG::sdl)
  target_link_libraries(sdl3_tutorial PRIVATE CONAN_PKG::sdl)
else()
  find_package(SDL3 CONFIG REQUIRED)
  target_link_libraries(sdl3_tutorial PRIVATE SDL3::SDL3)
endif()

add_subdirectory(tests)
