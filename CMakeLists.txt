project (ifc-reader)
cmake_minimum_required(VERSION 3.16)

include(ExternalProject)

set(VcpkgCMake ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(getDependentLibs FALSE)

if(WIN32)
    set(getDependentLibs TRUE)

    if(EXISTS ${VcpkgCMake} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed)
        find_package(Boost QUIET)
        if (Boost_FOUND)
            set(getDependentLibs FALSE)
        endif()
    endif()
endif()

# Can someone port this to linux?
IF (${getDependentLibs})

    ExternalProject_Add(vcpkg
       GIT_REPOSITORY https://github.com/microsoft/vcpkg
       CONFIGURE_COMMAND ""
       INSTALL_COMMAND ""
       BUILD_COMMAND ""
       UPDATE_COMMAND ""

       #test vcpkg bootstrap
       #UPDATE_COMMAND cd scripts/buildsystems
       #COMMAND git restore vcpkg.cmake

       SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
    )


    add_custom_target(get_vcpkg
        BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/vcpkg.exe
        COMMAND bootstrap-vcpkg.bat -disableMetrics:$$True
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
        DEPENDS vcpkg
    )

    add_custom_target(get_boost_iostreams ALL
        DEPENDS get_vcpkg
        COMMAND vcpkg.exe install boost-iostreams:x64-windows
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
    )

    add_custom_target(get_nlohmann-json ALL
        DEPENDS get_vcpkg get_boost_iostreams
        COMMAND vcpkg.exe install nlohmann-json:x64-windows
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
    )
endif()

if(EXISTS ${VcpkgCMake} AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed)
    include(${VcpkgCMake})
endif()

find_package(Boost QUIET)
if (Boost_FOUND)
    add_subdirectory(lib/core)
    add_subdirectory(lib/msvc)

    add_subdirectory(examples/dump-decls)
else()
    if (WIN32)
        add_custom_target(all_builds_complete ALL
            DEPENDS get_nlohmann-json
            DEPENDS get_boost_iostreams
            COMMAND echo ----------------------------------------------------------
            COMMAND echo - Re-generate cmake cache now                            -
            COMMAND echo ----------------------------------------------------------
        )
    endif()
endif()

