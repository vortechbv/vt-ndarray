# Copyright (c) 2017-2018 VORtech b.v.
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

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/tools/cmake")
include(vt/Util)

### User options

option(VT_ENABLE_TESTING "Build the test-suite" ON)
option(VT_ENABLE_BENCHMARKS "Build the benchmarks" ON)
option(VT_ENABLE_INSTALL "Enable installation of header files" ON)

set(
    VT_CATCH_DOWNLOAD_URL
    "https://github.com/catchorg/Catch2/releases/download/v2.4.0/catch.hpp"
    CACHE
    STRING "Url to the Catch header file.")
set(
    VT_CATCH_DOWNLOAD_SHA256
    41522232a2459bb0a078cb1fc8c20c0c082fd762afe2fb54cbb94f1aa538e244
    CACHE
    STRING "SHA256 hash of the Catch header file.")

set(
    VT_BENCHMARK_DOWNLOAD_URL
    "https://github.com/google/benchmark/archive/v1.4.1.tar.gz"
    CACHE
    STRING "Url to the Google Benchmark source code zip file.")
set(
    VT_BENCHMARK_DOWNLOAD_SHA256
    f8e525db3c42efc9c7f3bc5176a8fa893a9a9920bbd08cef30fb56a51854d60d
    CACHE
    STRING "SHA256 hash of the Google Benchmark zip file.")


### Build type configuration

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release)
endif()

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type specified, defaulting to Release.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()


### Third-party dependencies

set(_THIRDPARTY_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")
list(APPEND CMAKE_PREFIX_PATH "${_THIRDPARTY_DIR}")

if(MSVC)
    # MSVC can't link release libraries with debug libraries, so third-party
    # libraries will have to be built for the correct build type.
    if(CMAKE_CONFIGURATION_TYPES)
        # The build-dir contains multiple build types, so third-party libraries
        # will need to be build for both debug and release.
        set(_THIRDPARTY_BUILD_TYPE_ARG)
        set(_THIRDPARTY_BUILD_TYPES Debug Release)
    else()
        # The build dir contains a single build type, so third-party libraries
        # can be built for that build type.
        set(_THIRDPARTY_BUILD_TYPE_ARG -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}")
        set(_THIRDPARTY_BUILD_TYPES ${CMAKE_BUILD_TYPE})
    endif()
else()
    set(_THIRDPARTY_BUILD_TYPE_ARG "-DCMAKE_BUILD_TYPE=Release")
    set(_THIRDPARTY_BUILD_TYPES Release)
endif()


### Catch dependency

if(VT_ENABLE_TESTING)
    message(STATUS "Installing third-party catch library:")
    message("----------------------------------------")

    file(
        DOWNLOAD
            ${VT_CATCH_DOWNLOAD_URL}
            "${_THIRDPARTY_DIR}/include/catch2/catch.hpp"
        EXPECTED_HASH SHA256=${VT_CATCH_DOWNLOAD_SHA256}
        INACTIVITY_TIMEOUT 10
        SHOW_PROGRESS)

    add_library(Catch2::Catch2 INTERFACE IMPORTED)
    set_target_properties(
        Catch2::Catch2
        PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${_THIRDPARTY_DIR}/include")
endif()


### Benchmark dependency

if(VT_ENABLE_BENCHMARKS)
    message(STATUS "Installing third-party benchmark library:")
    message("--------------------------------------------")

    file(
        DOWNLOAD
            ${VT_BENCHMARK_DOWNLOAD_URL}
            "${_THIRDPARTY_DIR}/download/benchmark-1.4.1.tar.gz"
        EXPECTED_HASH SHA256=${VT_BENCHMARK_DOWNLOAD_SHA256}
        INACTIVITY_TIMEOUT 10
        SHOW_PROGRESS)

    vt_unzip(
        "${_THIRDPARTY_DIR}/download/benchmark-1.4.1.tar.gz"
        DEST "${_THIRDPARTY_DIR}/download")

    vt_cmake_configure(
        "${_THIRDPARTY_DIR}/download/benchmark-1.4.1"
        "${_THIRDPARTY_DIR}/build/benchmark"
        FLAGS
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DCMAKE_INSTALL_PREFIX=${_THIRDPARTY_DIR}
            -DCMAKE_DEBUG_POSTFIX=d
            ${_THIRDPARTY_BUILD_TYPE_ARG}
            -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
            -DBENCHMARK_ENABLE_TESTING=OFF)

    foreach(_BUILD_TYPE IN LISTS _THIRDPARTY_BUILD_TYPES)
        vt_cmake_build(
            "${_THIRDPARTY_DIR}/build/benchmark"
            FLAGS
                --config ${_BUILD_TYPE}
                --target install)
    endforeach()

    find_package(benchmark REQUIRED CONFIG)
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
    VT_NDARRAY_BENCHMARK_Clang_COMPILE_OPTIONS
    # Google Benchmark makes heavy use of global constructors
    -Wno-global-constructors)

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


### Test target

if(VT_ENABLE_TESTING)
    add_executable(
        vt-ndarray-test
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/allocator_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/container_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/test_main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/test/vt/ndarray/view_test.cpp")
    target_link_libraries(
        vt-ndarray-test
        vt-ndarray Catch2::Catch2)
    target_compile_options(
        vt-ndarray-test
        PRIVATE ${VT_NDARRAY_${CMAKE_CXX_COMPILER_ID}_COMPILE_OPTIONS})
endif()


### Benchmark target

if(VT_ENABLE_BENCHMARKS)
    add_executable(
        vt-ndarray-benchmark
        "${CMAKE_CURRENT_LIST_DIR}/benchmark/vt/ndarray/foreach_benchmark.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/benchmark/vt/ndarray/matrix_mul_benchmark.cpp")
    target_link_libraries(
        vt-ndarray-benchmark
        vt-ndarray benchmark::benchmark_main)
    target_compile_options(
        vt-ndarray-benchmark
        PRIVATE
            ${VT_NDARRAY_${CMAKE_CXX_COMPILER_ID}_COMPILE_OPTIONS}
            ${VT_NDARRAY_BENCHMARK_${CMAKE_CXX_COMPILER_ID}_COMPILE_OPTIONS})
endif()


### Install target

if(VT_ENABLE_INSTALL)
    install(
        DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/include/vt"
        DESTINATION include)
endif()
