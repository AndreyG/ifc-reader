find_package(GTest CONFIG REQUIRED)

add_executable(tests-msvc src/main.cpp)

target_link_libraries(tests-msvc PRIVATE ifc-msvc ifc-blob-reader GTest::gtest)
add_test(NAME msvc COMMAND tests-msvc ${CMAKE_CURRENT_SOURCE_DIR}/data)