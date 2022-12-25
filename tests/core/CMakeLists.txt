find_package(GTest CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams)

add_executable(tests-core src/main.cpp)

target_link_libraries(tests-core PRIVATE ifc-core GTest::gtest Boost::iostreams)