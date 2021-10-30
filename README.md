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

## Dependecies
`ifc-core` depends on [Boost::iostreams](https://www.boost.org/doc/libs/1_77_0/libs/iostreams/doc/index.html) for crossplatform implementation of file mapping.

`ifc-msvc` depends on [nlohmann::json](https://github.com/nlohmann/json) for reading `.d.json` configs produced by MSVC.

## Build
Nothing special, just plain CMake, something like this should be enough (after installing [Boost::iostreams](https://www.boost.org/doc/libs/1_77_0/libs/iostreams/doc/index.html)
and [nlohmann::json](https://github.com/nlohmann/json) mentioned [above](#Dependencies)):
```
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..
```
