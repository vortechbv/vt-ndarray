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

function(vt_unzip __FILENAME)
    cmake_parse_arguments(_ "" "DEST" "" ${ARGN})

    execute_process(
            COMMAND
                ${CMAKE_COMMAND} -E tar xfz
                "${__FILENAME}"
            WORKING_DIRECTORY "${__DEST}"
            RESULT_VARIABLE _UNZIP_RESULT)

    if(NOT _UNZIP_RESULT EQUAL "0")
        message(FATAL_ERROR "Unzip failed with code: ${_UNZIP_RESULT}")
    endif()
endfunction()

function(vt_cmake_configure __SRC_DIR __BUILD_DIR)
    cmake_parse_arguments(_ "" "" "FLAGS" ${ARGN})

    file(MAKE_DIRECTORY ${__BUILD_DIR})

    execute_process(
        COMMAND ${CMAKE_COMMAND} -G${CMAKE_GENERATOR} ${__FLAGS} "${__SRC_DIR}"
        WORKING_DIRECTORY "${__BUILD_DIR}"
        RESULT_VARIABLE _CMAKE_RESULT)

    if(NOT _CMAKE_RESULT EQUAL "0")
        message(FATAL_ERROR "CMake failed with code: ${_CMAKE_RESULT}")
    endif()
endfunction()

function(vt_cmake_build __BUILD_DIR)
    cmake_parse_arguments(_ "" "" "FLAGS" ${ARGN})

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build . ${__FLAGS}
        WORKING_DIRECTORY "${__BUILD_DIR}"
        RESULT_VARIABLE _CMAKE_RESULT)

    if(NOT _CMAKE_RESULT EQUAL "0")
        message(FATAL_ERROR "CMake build failed with code: ${_CMAKE_RESULT}")
    endif()
endfunction()
