# CMakeLists.txt --- CMake project settings
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.6)

# enable testing
enable_testing()

# project name and languages
project(VeySicK VERSION 0.5.0 LANGUAGES C CXX RC)

# We don't want dependency of runtime libraries
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "-static")
elseif(MSVC)
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
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

# options
option(ENABLE_PC8801    "Enable 8801 mode" ON)
option(ENABLE_PC9801    "Enable 9801 mode" ON)
option(INT_IS_32BIT     "Make VskInt 32-bit integer" OFF)
if(ENABLE_PC8801)
    add_definitions(-DENABLE_PC8801)
endif()
if(ENABLE_PC9801)
    add_definitions(-DENABLE_PC9801)
endif()
if(INT_IS_32BIT)
    add_definitions(-DINT_IS_32BIT)
endif()

##############################################################################
## Flex + Bison

find_package(FLEX 2.6.4)
find_package(BISON 3.0)

set(PARSER_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LEXER_OUT "${PARSER_DIR}/lexer.cpp")
set(PARSER_OUT "${PARSER_DIR}/parser.cpp")

if(FLEX_FOUND AND BISON_FOUND)
    set(PARSER_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    set(LEXER_OUT "${PARSER_DIR}/lexer.cpp")
    set(PARSER_OUT "${PARSER_DIR}/parser.cpp")

    set(ADDITIONAL_FLEX_FLAGS "-8")
    #set(ADDITIONAL_FLEX_FLAGS "-8")
    set(ADDITIONAL_BISON_FLAGS "-d -v -Wall -t -r all")
    #set(ADDITIONAL_BISON_FLAGS "-d -v -Wall")

    flex_target(LEXER lexer.ll "${LEXER_OUT}"
                DEFINES_FILE "${PARSER_DIR}/lexer.h"
                COMPILE_FLAGS ${ADDITIONAL_FLEX_FLAGS})
    bison_target(PARSER parser.yy "${PARSER_OUT}"
                 DEFINES_FILE "${PARSER_DIR}/parser.h"
                 COMPILE_FLAGS ${ADDITIONAL_BISON_FLAGS})
    add_flex_bison_dependency(LEXER PARSER)
endif()

if(WIN32)
    add_definitions(-DYY_NO_UNISTD_H)
endif()

##############################################################################
# OpenAL - Audio library
# Please set OPENALDIR environment variable.

find_package(OpenAL)

if(OpenAL_FOUND)
    # Tell the preprocessor OpenAL existence
    add_definitions(-DHAVE_OPENAL)

    # workaround for including <AL/alut.h>
    include_directories("${OPENAL_INCLUDE_DIR}" "${OPENAL_INCLUDE_DIR}/..")
endif()

##############################################################################
# alut

option(BUILD_EXAMPLES "build example applications" OFF)
option(BUILD_TESTS "build the test-suite" OFF)
if(OpenAL_FOUND)
    if(NOT BUILD_SHARED_LIBS)
        add_definitions(-DALUT_STATIC)
    endif()
    add_subdirectory(freealut)
endif()

##############################################################################
# fmgon

add_subdirectory(fmgon)

##############################################################################
# Display current status

message(STATUS "OPENAL_INCLUDE_DIR: ${OPENAL_INCLUDE_DIR}")
message(STATUS "OPENAL_LIBRARY: ${OPENAL_LIBRARY}")
message(STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message(STATUS "BUILD_EXAMPLES: ${BUILD_EXAMPLES}")
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}")

##############################################################################
# LIMEJAM.exe

add_executable(LIMEJAM LIMEJAM.c)

# shuffle lines in commands.h
add_custom_target(jam
    COMMAND "${CMAKE_CURRENT_BINARY_DIR}/LIMEJAM" -k "${CMAKE_CURRENT_SOURCE_DIR}/insn.h"
    DEPENDS LIMEJAM)

##############################################################################
# VeySicK

# VeySicK.exe
add_executable(VeySicK WIN32
    VeySicK.cpp
    coreapi.cpp
    draw.cpp
    encoding.cpp
    mdbg.cpp
    mem.cpp
    print_using.cpp
    renum.cpp
    turtle.cpp
    vm8801.cpp
    vm9801.cpp
    random.cpp
    win.cpp
    "${LEXER_OUT}"
    "${PARSER_OUT}"
    sound.cpp
    VeySicK_res.rc)
target_compile_definitions(VeySicK PRIVATE UNICODE _UNICODE JAPAN)
target_include_directories(VeySicK PRIVATE "${PARSER_DIR}")
target_link_libraries(VeySicK comctl32 imm32 shell32 ole32 uuid shlwapi gdiplus imm32 fmgon alut ${OPENAL_LIBRARY})
if(MSVC)
    target_link_options(VeySicK PRIVATE /MANIFEST:NO)
endif()

##############################################################################
