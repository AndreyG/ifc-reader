# IFC Reader
This is C++ library for reading [ifc](https://github.com/microsoft/ifc-spec)-files.
Actually there are 2 separate libraries: `ifc-core` and `ifc-msvc`.

The reason for this is the following: ifc could contain references to other modules.
For example, [the following module interface](https://github.com/Klaim/cxx20-modules-examples/blob/master/hello-module/hello/hello.mxx)
```
export module hello;

import <string_view>;

export namespace hello {
  void say_hello(std::string_view name);
}
```
depends on type `std::string_view` defined in outer header unit `<string_view>` (see `struct` [DeclReference](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Declaration.h#L402)).
Conseqeuntly for reading and understanding of some ifc-file it's needed to be able to find and read other ifc-files.
How to do it is not specified in [IFC specification](https://github.com/microsoft/ifc-spec) itself and depends on a compiler/build system.
To solve this problem library `ifc-core` uses interface [`Environment`](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Environment.h)
and library `ifc-msvc` provides its implementation [`MSVCEnvironment`](https://github.com/AndreyG/ifc-reader/blob/master/lib/msvc/include/ifc/MSVCEnvironment.h).

# Dependecies
`ifc-core` doesn't have external dependencies, but requires C++20 for compilation.

`ifc-msvc` depends on [Boost::iostreams](https://www.boost.org/doc/libs/1_81_0/libs/iostreams/doc/index.html) for crossplatform implementation of file mapping
and [nlohmann::json](https://github.com/nlohmann/json) for reading `.d.json` configs produced by MSVC.

Tests depends on [GoogleTest](https://github.com/google/googletest).
# Build
Nothing special, just plain CMake, something like this should be enough (after installing [Boost::iostreams](https://www.boost.org/doc/libs/1_81_0/libs/iostreams/doc/index.html)
and [nlohmann::json](https://github.com/nlohmann/json) mentioned [above](#Dependencies), and optionally [GoogleTest](https://github.com/google/googletest)):
```
mkdir build
cd build
cmake ..
```
To build tests switch on CMake option `BUILD_IFC_READER_TESTS`, to build examples -- `BUILD_IFC_READER_EXAMPLES` (see top-level [CMakeLists.txt](https://github.com/AndreyG/ifc-reader/blob/master/CMakeLists.txt)).
### Windows
[Vcpkg](https://github.com/microsoft/vcpkg) could be used for fetching required dependencies. If it's not installed yet, you could run the following commands for pulling package manager itself:

    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    bootstrap-vcpkg.bat
    
And then install required dependencies: 

    vcpkg.exe install boost-iostreams:x64-windows
    vcpkg.exe install nlohmann-json:x64-windows
    
for tests (optionally):

    vcpkg.exe install gtest:x64-windows

After that you could generate normal Visual Studio solution:
```
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake ..
```
or work with CMake directly in Visual Studio.

#### Visual Studio

From Visual Studio, open `CMakeLists.txt`

After `cmake` wizard pops up, open the `CMake Settings Editor`

In `CMake toolchain file` - browse and select `vcpkg\scripts\buildsystems\vcpkg.cmake`

Delete cache, generate cache.

Build solution normally.
