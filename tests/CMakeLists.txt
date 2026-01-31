add_executable(unit_tests test_main.cpp)

target_compile_features(unit_tests PRIVATE cxx_std_20)

if(TARGET CONAN_PKG::catch2)
  target_link_libraries(unit_tests PRIVATE CONAN_PKG::catch2)
else()
  find_package(Catch2 REQUIRED)
  target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
endif()

add_test(NAME unit_tests COMMAND unit_tests)
