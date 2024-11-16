# CMakeLists.txt --- CMake project settings
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.6)

# Adopt new policy CMP0077
cmake_policy(SET CMP0077 NEW)

# enable testing
enable_testing()

# project name and languages
project(fmgon VERSION 0.0 LANGUAGES CXX)

# We don't want dependency of runtime libraries
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif (MSVC)
    # replace "/MD" with "/MT" (building without runtime DLLs)
    set(CompilerFlags
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    foreach(CompilerFlags ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlags} "${${CompilerFlags}}")
    endforeach()
endif()

# UTF-8
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

##############################################################################
# fmgon

# libfmgon.a
add_library(fmgon STATIC
    fmgen.cpp
    fmtimer.cpp
    opm.cpp
    opna.cpp
    posix_pevent.cpp
    psg.cpp
    soundplayer.cpp
    YM2203.cpp
    YM2203_Timbre.cpp)
target_include_directories(fmgon PUBLIC ../freealut/include)
target_link_libraries(fmgon PRIVATE ${OPENAL_LIBRARY} ${ALUT_LIBRARY})

##############################################################################
