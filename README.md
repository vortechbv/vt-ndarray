vt-ndarray
==========

[![Build Status](https://github.com/vortechbv/vt-ndarray/actions/workflows/ci.yml/badge.svg)](https://github.com/vortechbv/vt-ndarray/actions/workflows/ci.yml)

N-dimensional array library for C++, developed and maintained by [VORtech](https://vortech.nl/).

Getting started
---------------

This is a header-only library. To use it, simply add all files under `include` to your include directories. The library uses C++17 features and assumes a C++17 compliant compiler. Compatibility with the following compilers is tested:

- GCC 14.2
- Clang 18.1
- MSVC vs2022

The library provides an array container that allows for N-dimensional indexing:

```c++
#include <vt/ndarray.hpp>
#include <cassert>

int main()
{
    // Creates a 2-by-3 array of integers with initial values.
    const vt::ndarray<int, 2> A{{ 2, 3 }, {
        3, 1, 4,
        1, 5, 9
    }};

    assert(A[0][0] == 3); assert(A[0][1] == 1); assert(A[0][2] == 4);
    assert(A[1][0] == 1); assert(A[1][1] == 5); assert(A[1][2] == 9);
}
```

In many use-cases, array data is managed externally, e.g. by external libraries, clients of your library, `malloc`, `std::vector`, etc. To prevent having to copy that data into the `vt::ndarray` container, array views are provided. By using views in your function interfaces, you can use the N-dimensional indexing regardless of the array's origin:

```c++
#include <vt/ndarray.hpp>
#include <cassert>

static void diag(vt::ndarray_view<int, 2> A, vt::ndarray_view<const int, 1> d)
{
    const size_t n = d.shape(0);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            A[i][j] = 0;
        }
        A[i][i] = d[i];
    }
}

int main()
{
    const vt::ndarray<int, 1> d{{ 3 }, { 1, 2, 3 }};
    int A[9];

    // A 3-by-3 view is created with `A` as array data.
    // `d` is automatically converted to a view.
    diag({ { 3, 3 }, A }, d);

    assert(A[0] == 1); assert(A[1] == 0); assert(A[2] == 0);
    assert(A[3] == 0); assert(A[4] == 2); assert(A[5] == 0);
    assert(A[6] == 0); assert(A[7] == 0); assert(A[8] == 3);
}
```

A reference section containing documentation of the API and further usage examples can be found [here](doc/vt/ndarray/readme.md#top).

For maintainers
---------------

To build the accompanying test suite, you will need CMake 3.8 or newer. Instructions follow below.

### Building

First, you will need to use CMake to generate build files for your platform:

```
mkdir <build-dir>
cd <build-dir>
cmake <vt-ndarray-root-dir>
```

Here `<build-dir>` can be any directory. It is advised to pick a directory outside of the project's source tree, e.g. to avoid the build files from showing up when `grep`-ing the source tree. The `<vt-ndarray-root-dir>` is the directory that contains the `CMakeLists.txt`-file.

After generating the build files, you can build the test suite using the build files' native method. For example, if Unix Makefiles were generated, you can run `make`, or if a Visual Studio solution was generated, you can use `msbuild` or the Visual Studio IDE.

The install script is executed when building the `install`-target.

### Testing

You can run the test suite by executing `vt-ndarray-test`/`vt-ndarray-test.exe`. Run with `--help` for more options. Note that Visual Studio places the output binaries in a `Debug`/`Release` subdirectory of your build directory.

### Benchmarks

Benchmarks are included for measuring the overhead of the N-dimensional array classes compared to raw pointers. You can run them by executing `vt-ndarray-test [!benchmark]`/`vt-ndarray-test.exe [!benchmark]`. Run with `--help` for more options.

### Options

Common CMake options for the build are listed below. See the CMake documentation for more options.

#### Build Type

Some build systems (such as Visual Studio) have multiple build types. For build systems with only one build type (such as Makefiles) the default build type will be `Release`. To specify a different build type, add the `-DCMAKE_BUILD_TYPE=<build-type>` flag when executing CMake.

The available build types are: `Debug` and `Release`.

#### Optional compilation

Compilation of the test suite is not mandatory. You can disable it by adding the `-DVT_ENABLE_TESTING=OFF` flag when executing CMake.

#### External Libraries

For testing purposes, vt-ndarray uses the Catch2 testing framework. By default, Catch2 will be downloaded from the internet, unless you specified to disable the compilation of the test suite. If the download is not possible, you can specify an alternative download location.

To specify an alternative download location for Catch2, add the `-DVT_CATCH_DOWNLOAD_URL=<url>` and `-DVT_CATCH_DOWNLOAD_SHA256=<hash>` flags when executing CMake. Here `<url>` should lead to the Catch single include header file and `<hash>` must be the SHA256 hash of the header file.
