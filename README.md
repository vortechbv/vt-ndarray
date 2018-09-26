vt-ndarray
==========

The VORtech N-dimensional array library for C++.

Prerequisites
-------------

This is a header-only library. To use it, simply add all files under `include` to your include directories.

This library uses C++17 features and assumes a C++17 compliant compiler.

To use the install script or build the accompanying test-suite, you will need CMake 3.8 or newer.

Documentation
-------------

A reference sections containing documentation of the API and usage examples can be found [here](doc/vt/ndarray/readme.md#top).

Building
--------

First, you will need to use CMake to generate build files for your platform:

```
mkdir <build-dir>
cd <build-dir>
cmake <vt-ndarray-root-dir>
```

Here `<build-dir>` can be any directory, but it is advised to pick a directory outside of the project's source tree. (For example to avoid the build files from showing up when `grep`-ing the source tree.) The `<vt-ndarray-root-dir>` is the directory that contains the `CMakeLists.txt`-file.

After generating the build files, you can build the test-suite using the build files' native method. For example, if Unix Makefiles were generated, you can run `make`, or if a Visual Studio solution was generated, you can use `msbuild` or the Visual Studio IDE.

The install script is executed when building the `install`-target.

Testing
-------

You can run the test-suite by executing `vt-ndarray-test`/`vt-ndarray-test.exe`. Run with `--help` for more options. Note that Visual Studio places the output binaries in a `Debug`/`Release` subdirectory of your build directory.

Options
-------

Common CMake options for the build are listed below. See the CMake documentation for more options.

### Build Type

Some build systems (such as Visual Studio) have multiple build types. For build systems with only one build type (such as Makefiles) the default build type will be `Release`. To specify a different build type, add the `-DCMAKE_BUILD_TYPE=<build-type>` flag when executing CMake.

The available build types are: `Debug`, `Release`, `RelWithDebInfo` and `MinSizeRel`.

### External Libraries

vt-ndarray uses the Catch testing framework. By default, Catch will be downloaded from the internet. If the download is not possible, (because the URL no longer exists or if you're not connected to the internet,) you can specify an alternative download location.

To specify an alternative download location, add the `-DVT_CATCH_DOWNLOAD_URL=<url>` and `-DVT_CATCH_DOWNLOAD_SHA256=<hash>` flags when executing CMake. Here `<url>` should lead to the Catch single include header file and `<hash>` must be the SHA256 hash of the header file.
