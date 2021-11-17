find_package(Boost REQUIRED COMPONENTS iostreams)


add_executable(dump-decls main.cpp Presenter.h Presenter.cpp)

target_include_directories(dump-decls PUBLIC ${Boost_INCLUDE_DIR} )

target_link_libraries(dump-decls ifc-msvc)
