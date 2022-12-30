# IFC Reader
This is C++ library for reading [ifc](https://github.com/microsoft/ifc-spec)-files (`ifc-core`) and 2 optional extra tiny libraries,
namely `ifc-msvc` and `ifc-blob-reader`.
The reason for this separation is the following: `ifc-core` doesn't want to know anything about files, configs and so on.
The entry point for IFC-reading -- `ifc::File` -- is constructed from [BlobView](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/File.h#L200) 
and how to get `BlobView` is responsibility of library users.

Tests and examples do it via single-function library [ifc-blob-reader](https://github.com/AndreyG/ifc-reader/tree/master/lib/blob-reader)
wrapping [Boost::iostreams](https://www.boost.org/doc/libs/1_81_0/libs/iostreams/doc/index.html).

One more issue arising during inspecting IFC is how to process cross-module references.
For example, [the following module interface](https://github.com/Klaim/cxx20-modules-examples/blob/master/hello-module/hello/hello.mxx)
```
export module hello;

import <string_view>;

export namespace hello {
  void say_hello(std::string_view name);
}
```
depends on type `std::string_view` defined in outer header unit `<string_view>`
(see [`struct DeclReference`](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Declaration.h#L402)).
Conseqeuntly during inspecting some ifc-file it may be necessary to find other ifc-files.
How to do it is not specified in [IFC specification](https://github.com/microsoft/ifc-spec) itself and depends on a compiler/build system.
In `ifc-core` this is done via class [Environment](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Environment.h#L13)
receiving [Config](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Environment.h#L25)
and library `ifc-msvc` [provides](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Environment.h#L25) such config,
reading it from `.json` [produced by MSVC](https://docs.microsoft.com/en-us/cpp/build/reference/sourcedependencies).

# Dependecies
`ifc-core` doesn't have external dependencies, but requires C++20 for compilation.

`ifc-blob-reader` depends on [Boost::iostreams](https://www.boost.org/doc/libs/1_81_0/libs/iostreams/doc/index.html) for crossplatform implementation of file mapping.

`ifc-msvc` depends on [nlohmann::json](https://github.com/nlohmann/json) for reading `.json` configs produced by MSVC.

Tests depend on [GoogleTest](https://github.com/google/googletest).
# Build
  0. If tests or examples are needed, then install required dependencies, mentioned [above](#Dependencies). It not, then go to step 1.
  1. Just run CMake, something like this should be enough:
```
mkdir build
cd build
cmake ..
```
To build tests switch on CMake option `BUILD_IFC_READER_TESTS`, to build examples -- `BUILD_IFC_READER_EXAMPLES` (see top-level [CMakeLists.txt](https://github.com/AndreyG/ifc-reader/blob/master/CMakeLists.txt)).
### Windows
[Vcpkg](https://github.com/microsoft/vcpkg) could be used for fetching dependencies. If it's not installed yet, you could run the following commands for pulling package manager itself:

    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    bootstrap-vcpkg.bat
    
And then install dependencies (required for both tests and examples): 

    vcpkg.exe install boost-iostreams:x64-windows
    vcpkg.exe install nlohmann-json:x64-windows
    
and `GoogleTest` required only for tests:

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
