# IFC Reader
This is C++ library for reading [ifc](https://github.com/microsoft/ifc-spec)-files (`ifc-core` and its more user friendly interface `reflifc`) and 2 optional extra tiny libraries,
namely `ifc-msvc` and `ifc-blob-reader`.
The reason for this separation is the following: `ifc-core` and `reflifc` don't want to know anything about files, configs and so on.
The entry point for IFC-reading -- `ifc::File` -- is constructed from [BlobView](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/File.h#L204)
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
(see [`struct DeclReference`](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Declaration.h#L401)).
Conseqeuntly during inspecting some ifc-file it may be necessary to find other ifc-files.
How to do it is not specified in [IFC specification](https://github.com/microsoft/ifc-spec) itself and depends on a compiler/build system.
In `ifc-core` this is done via class [Environment](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Environment.h#L13)
receiving [Config](https://github.com/AndreyG/ifc-reader/blob/master/lib/core/include/ifc/Environment.h#L25)
and library `ifc-msvc` [provides](https://github.com/AndreyG/ifc-reader/blob/master/lib/msvc/include/ifc/MSVCEnvironment.h#L7) such config,
reading it from `.json` [produced by MSVC](https://docs.microsoft.com/en-us/cpp/build/reference/sourcedependencies).

# How to use

This project contains a demonstration application [`dump-decls`](https://github.com/AndreyG/ifc-reader/bllob/master/examples/dump-decls/main.cpp), which allows you do display the declarations in an IFC file.

To use `dump-decls` (or to generate information that can be loaded by `ifc-reader`), you need to compile your module into its IFC file, as well as generating its associated ["source dependencies"](https://docs.microsoft.com/en-us/cpp/build/reference/sourcedependencies).

For example, consider the following file (based on [`hello.mxx`](https://github.com/Klaim/cxx20-modules-examples/blob/master/hello-module/hello/hello.mxx)), but it should be called something like `hello.cpp`, as `.mxx` is not an extension recognised by MSVC:

```cpp
export module hello;

import std.core;

export namespace hello {
  void say_hello(uint32_t count);
}
```

You need compile this MSVC and generate its "source dependencies":

```bash
cl.exe /W4 /WX /experimental:module /interface /sourceDependencies . /std:c++latest /EHsc /MD /c hello.cpp
```

This will generate two files:

* `hello.ifc` -- the binary module interface (that this repository aims to parse); and

* `hello.cpp.json` -- the source dependencies for `hello.cpp` (*note*: the name of this `.json` is the name of your source file and *not* the name of your module; if your module has a different name, then the name of the IFC may not match your source file name)

The source dependencies look something like:

```json
{
    "Version": "1.1",
    "Data": {
        "Source": "C:\\path\\to\\src\\hello.cpp",
        "ProvidedModule": "hello",
        "Includes": [],
        "ImportedModules": [
            {
                "Name": "std.core",
                "BMI": "C:\\path\\to\\visual_studio\\MSVC\\14.30.30705\\ifc\\x64\\release\\std.core.ifc"
            }
        ],
        "ImportedHeaderUnits": []
    }
```

You can then call `dump-decls` as follows:

```bash
/path/to/ifc-reader/build/examples/dump-decls/dump-decls.exe hello.ifc
```

which will give you (at the time of writing):

```
IFC Version: 0.40
File contains 14 partitions
Global Scope Index: 1
Total declarations count: 2
Scopes count: 2
Count of declarations from all scopes: 2
-------------------------------------- Global Scope --------------------------------------
Namespace 'hello' {
  Function 'say_hello', type: void(unsigned int)
}
```

## A note on `wine`

If you wish to use `cl.exe` under `wine` but compile `ifc-reader` *natively* under Linux, then this is possible, but you must correct the paths in the source dependencies to point to _native_ file paths before calling `dump-decls`. For example, if `cl.exe` (when run under `wine`) gives you:

* `z:\\home\\avj\\clones\\ifc-reader\\how_to\\hello.cpp`

in the source dependencies, then you need to edit the json to have:

* `/home/avj/clones/ifc-reader/how_to/hello.cpp`

which is the output from:

* `readlink -f $(wine64 winepath -u "z:\\home\\avj\\clones\\ifc-reader\\how_to\\hello.cpp")`

After changing all paths to be their Linux equivalents, you can then load your IFC file with `dump-decls`

# Building from source

## Dependencies 
`ifc-core` and `reflifc` don't have external dependencies, but require C++20 for compilation.

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
