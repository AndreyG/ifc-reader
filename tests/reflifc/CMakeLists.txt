find_package(GTest CONFIG REQUIRED)

add_executable(reflifc-tests src/main.cpp)

target_link_libraries(reflifc-tests PRIVATE reflifc ifc-blob-reader GTest::gtest)
add_test(NAME reflifc COMMAND reflifc-tests ${CMAKE_CURRENT_SOURCE_DIR}/data)