// Copyright (c) 2026 VORtech b.v.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <vt/ndarray/index.hpp>

#include <catch2/catch.hpp>


TEST_CASE(
    "vt::index_range_count_v can be used to count the number of index ranges "
    "in a parameter pack of indexers",
    "[ndarray][index]"
) {
    STATIC_REQUIRE(vt::index_range_count_v<1, std::size_t> == 0);
    STATIC_REQUIRE(vt::index_range_count_v<1, int> == 0);
    STATIC_REQUIRE(vt::index_range_count_v<1, vt::index_range<0>> == 1);
    STATIC_REQUIRE(vt::index_range_count_v<1, vt::index_range<1>> == 1);

    STATIC_REQUIRE(vt::index_range_count_v<2, std::size_t, std::size_t> == 0);
    STATIC_REQUIRE(vt::index_range_count_v<2, std::size_t, int> == 0);
    STATIC_REQUIRE(vt::index_range_count_v<2, std::size_t, vt::index_range<0>> == 1);
    STATIC_REQUIRE(vt::index_range_count_v<2, std::size_t, vt::index_range<1>> == 1);

    STATIC_REQUIRE(vt::index_range_count_v<2, int, std::size_t> == 0);
    STATIC_REQUIRE(vt::index_range_count_v<2, int, int> == 0);
    STATIC_REQUIRE(vt::index_range_count_v<2, int, vt::index_range<0>> == 1);
    STATIC_REQUIRE(vt::index_range_count_v<2, int, vt::index_range<1>> == 1);

    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<0>, std::size_t> == 1);
    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<0>, int> == 1);
    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<0>, vt::index_range<0>> == 2);
    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<0>, vt::index_range<1>> == 2);

    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<1>, std::size_t> == 1);
    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<1>, int> == 1);
    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<1>, vt::index_range<0>> == 2);
    STATIC_REQUIRE(vt::index_range_count_v<2, vt::index_range<1>, vt::index_range<1>> == 2);
}


TEST_CASE(
    "vt::is_slice_contiguous can be used to check if a parameter pack of "
    "indices and index ranges would results in a contiguous slice or not",
    "[ndarray][index]"
) {
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<vt::index_range<0>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<vt::index_range<1>>);

    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, std::size_t>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, vt::index_range<0>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, vt::index_range<1>>);

    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, std::size_t>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, vt::index_range<0>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, vt::index_range<1>>);

    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<1>>);

    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<1>>);

    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, std::size_t, std::size_t>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, std::size_t, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, std::size_t, vt::index_range<0>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, std::size_t, vt::index_range<1>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, int, std::size_t>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, int, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, int, vt::index_range<0>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, int, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<std::size_t, vt::index_range<0>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<std::size_t, vt::index_range<0>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, vt::index_range<0>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<std::size_t, vt::index_range<0>, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<std::size_t, vt::index_range<1>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<std::size_t, vt::index_range<1>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<std::size_t, vt::index_range<1>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<std::size_t, vt::index_range<1>, vt::index_range<1>>);

    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, std::size_t, std::size_t>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, std::size_t, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, std::size_t, vt::index_range<0>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, std::size_t, vt::index_range<1>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, int, std::size_t>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, int, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, int, vt::index_range<0>>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, int, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<int, vt::index_range<0>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<int, vt::index_range<0>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, vt::index_range<0>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<int, vt::index_range<0>, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<int, vt::index_range<1>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<int, vt::index_range<1>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<int, vt::index_range<1>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<int, vt::index_range<1>, vt::index_range<1>>);

    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, std::size_t, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, std::size_t, int>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, std::size_t, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, std::size_t, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, int, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, int, int>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, int, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, int, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<0>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<0>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<0>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<0>, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<1>, int>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<1>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<0>, vt::index_range<1>, vt::index_range<1>>);

    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, std::size_t, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, std::size_t, int>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, std::size_t, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, std::size_t, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, int, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, int, int>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, int, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, int, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<0>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<0>, int>);
    STATIC_REQUIRE( vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<0>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<0>, vt::index_range<1>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<1>, std::size_t>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<1>, int>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<1>, vt::index_range<0>>);
    STATIC_REQUIRE(!vt::is_slice_contiguous_v<vt::index_range<1>, vt::index_range<1>, vt::index_range<1>>);
}
