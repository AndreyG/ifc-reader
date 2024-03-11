find_package(GTest CONFIG REQUIRED)

add_executable(tests-core src/main.cpp)

target_link_libraries(tests-core PRIVATE ifc-core ifc-blob-reader GTest::gtest)
add_test(NAME core COMMAND tests-core ${CMAKE_CURRENT_SOURCE_DIR}/data)