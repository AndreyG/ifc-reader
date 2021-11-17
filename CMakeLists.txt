project (ifc-reader)
cmake_minimum_required(VERSION 3.16)

include(ExternalProject)

set(AddMainProjects TRUE)

# Can someone port this to linux?
IF (WIN32)
    set(AddMainProjects FALSE)

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
        DEPENDS get_vcpkg
        COMMAND vcpkg.exe install nlohmann-json:x64-windows
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
    )

    set(VcpkgCMake ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed
 
        #test vcpkg bootstrap
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems
    )

    if(NOT EXISTS ${VcpkgCMake} OR NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed)
        message("IMPORTANT: Run compilation again to update cmake project")
    else()
        set(AddMainProjects TRUE)
        include(${VcpkgCMake})
    endif()

endif()

if(${AddMainProjects})
    add_subdirectory(lib/core)
    add_subdirectory(lib/msvc)

    add_subdirectory(examples/dump-decls)
endif()

