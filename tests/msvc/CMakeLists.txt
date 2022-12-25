find_package(GTest CONFIG REQUIRED)

add_executable(tests-msvc src/main.cpp)

target_link_libraries(tests-msvc PRIVATE ifc-msvc GTest::gtest)