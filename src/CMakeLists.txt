add_executable(sdl3_tutorial main.cpp)

target_compile_features(sdl3_tutorial PRIVATE cxx_std_20)

if(TARGET CONAN_PKG::sdl)
  target_link_libraries(sdl3_tutorial PRIVATE CONAN_PKG::sdl)
else()
  find_package(SDL3 CONFIG REQUIRED)
  target_link_libraries(sdl3_tutorial PRIVATE SDL3::SDL3)
endif()
