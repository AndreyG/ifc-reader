# IFC Reader (!!! WIP, very early stage !!!)
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
depends on type `std::string_view` defined in outer header unit `<string_view>`.
Conseqeuntly for reading and understanding of some ifc-file it's needed to be able to find and read other ifc-files.
How to do it is not specified in [IFC specification](https://github.com/microsoft/ifc-spec) itself and depends on a compiler/build system.
To solve this problem library `ifc-core` uses interface [`Environment`](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Environment.h)
and library `ifc-msvc` provides its implementation [`MSVCEnvironment`](https://github.com/AndreyG/ifc-reader/blob/master/lib/msvc/include/ifc/MSVCEnvironment.h).

# Dependecies
`ifc-core` depends on [Boost::iostreams](https://www.boost.org/doc/libs/1_77_0/libs/iostreams/doc/index.html) for crossplatform implementation of file mapping.

`ifc-msvc` depends on [nlohmann::json](https://github.com/nlohmann/json) for reading `.d.json` configs produced by MSVC.

# Build
### In Linux

Nothing special, just plain CMake, something like this should be enough (after installing [Boost::iostreams](https://www.boost.org/doc/libs/1_77_0/libs/iostreams/doc/index.html)
and [nlohmann::json](https://github.com/nlohmann/json) mentioned [above](#Dependencies)):

```
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..
```



### In Windows

Run following commands:

    git clone https://github.com/microsoft/vcpkg
    cd vcpkg
    bootstrap-vcpkg.bat
    vcpkg.exe install boost-iostreams:x64-windows
    vcpkg.exe install nlohmann-json:x64-windows

From Visual Studio, open `CMakeFile.txt`

After `cmake` wizard pops up, open the `CMake Settings Editor`

In `CMake toolchain file` - browse and select `vcpkg\scripts\buildsystems\vcpkg.cmake`

Delete cache, generate cache.

Build solution normally.

