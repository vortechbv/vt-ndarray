# Copyright (c) 2017-2026 VORtech b.v.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(vt-ndarray CXX)

include(FetchContent)

### User options

option(VT_ENABLE_TESTING "Build the test-suite" ON)
option(VT_ENABLE_INSTALL "Enable installation of header files" ON)

set(
    VT_CATCH_GIT_REPOSITORY
    "https://github.com/catchorg/Catch2.git"
    CACHE
    STRING "Url to the Catch git repository. Can be a local clone.")


### Build type configuration

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type specified, defaulting to Release.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()


### Catch dependency

if(VT_ENABLE_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY ${VT_CATCH_GIT_REPOSITORY}
        GIT_TAG v2.13.9
    )

    FetchContent_MakeAvailable(Catch2)

    get_target_property(
        CATCH2_INCLUDE_DIRS
        Catch2
        INTERFACE_INCLUDE_DIRECTORIES
    )
    set_target_properties(
        Catch2
        PROPERTIES
            INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${CATCH2_INCLUDE_DIRS}"
    )
endif()


### Compile options

set(
    VT_NDARRAY_GNU_COMPILE_OPTIONS
    -pedantic-errors
    -Wall
    -Wextra
    -Wcast-align
    -Wcast-qual
    -Wfloat-equal
    -Wlogical-op
    -Wmissing-include-dirs
    -Wold-style-cast
    -Woverloaded-virtual
    -Wsign-conversion
    -Wsuggest-override
    -Wundef
    -Wuseless-cast)

set(
    VT_NDARRAY_Clang_COMPILE_OPTIONS
    -pedantic-errors
    -Weverything
    -Wno-c++98-compat
    -Wno-c++98-compat-pedantic
    -Wno-missing-braces
    -Wno-padded)

set(
    VT_NDARRAY_MSVC_COMPILE_OPTIONS
    /W4
    /volatile:iso
    /Zc:strictStrings
    /Zc:rvalueCast)


### Header-only library target

add_library(vt-ndarray INTERFACE)
target_include_directories(
    vt-ndarray
    INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_features(
    vt-ndarray
    INTERFACE cxx_std_17)

add_library(vt::ndarray ALIAS vt-ndarray)


### Test target

if(VT_ENABLE_TESTING)
    add_executable(
        vt-ndarray-test
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/allocator_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/container_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/foreach_benchmark.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/matrix_mul_benchmark.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/test_main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/view_test.cpp")
    target_link_libraries(
        vt-ndarray-test
        vt-ndarray Catch2::Catch2)
    target_compile_options(
        vt-ndarray-test
        PRIVATE ${VT_NDARRAY_${CMAKE_CXX_COMPILER_ID}_COMPILE_OPTIONS})
    target_compile_definitions(
        vt-ndarray-test
        PRIVATE CATCH_CONFIG_ENABLE_BENCHMARKING)
endif()


### Install target

if(VT_ENABLE_INSTALL)
    install(
        DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/include/vt"
        DESTINATION include)
endif()
