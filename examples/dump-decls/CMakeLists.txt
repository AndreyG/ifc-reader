find_package(Boost REQUIRED COMPONENTS iostreams)

add_executable(dump-decls main.cpp Presenter.h Presenter.cpp)
target_link_libraries(dump-decls ifc-msvc Boost::iostreams)
