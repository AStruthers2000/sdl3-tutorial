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

add_subdirectory(src)
add_subdirectory(tests)
