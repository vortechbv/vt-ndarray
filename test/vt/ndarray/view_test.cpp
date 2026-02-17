// Copyright (c) 2017-2026 VORtech b.v.
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

#include <vt/ndarray/view.hpp>

#include <catch2/catch.hpp>
#include <algorithm>
#include <memory>
#include <numeric>
#include <sstream>


TEST_CASE(
    "A vt::ndview is a pointer-shape pair",
    "[ndarray][view]"
) {
    const int data[4] = { 0 };
    const vt::ndview<const int, 2> view{{ 2, 2 }, data};

    REQUIRE(view.shape(0) == 2);
    REQUIRE(view.shape(1) == 2);
    REQUIRE(view.data() == data);
}


TEST_CASE(
    "A vt::ndview can index into 1-dimensional data",
    "[ndarray][view]"
) {
    const int data[4] = { 3, 1, 4, 1 };
    const vt::ndview<const int, 1> view{{ 4 }, data};

    REQUIRE(view.shape(0) == 4);

    CHECK(view[0] == 3);
    CHECK(view[1] == 1);
    CHECK(view[2] == 4);
    CHECK(view[3] == 1);
}


TEST_CASE(
    "A vt::ndview can index into 2-dimensional data",
    "[ndarray][view]"
) {
    const int data[6] = {
        3, 1, 4,
        1, 5, 9
    };
    const vt::ndview<const int, 2> view{{ 2, 3 }, data};

    REQUIRE(view.shape(0) == 2);
    REQUIRE(view.shape(1) == 3);

    CHECK(view[0][0] == 3);
    CHECK(view[0][1] == 1);
    CHECK(view[0][2] == 4);
    CHECK(view[1][0] == 1);
    CHECK(view[1][1] == 5);
    CHECK(view[1][2] == 9);
}


TEST_CASE(
    "A vt::ndview can index into 3-dimensional data",
    "[ndarray][view]"
) {
    const int data[24] = {
        3, 1, 4, 1,
        5, 9, 2, 6,
        5, 3, 5, 8,

        9, 7, 9, 3,
        2, 3, 8, 4,
        6, 2, 6, 4
    };
    const vt::ndview<const int, 3> view{{ 2, 3, 4 }, data};

    REQUIRE(view.shape(0) == 2);
    REQUIRE(view.shape(1) == 3);
    REQUIRE(view.shape(2) == 4);

    CHECK(view[0][0][0] == 3);
    CHECK(view[0][0][1] == 1);
    CHECK(view[0][0][2] == 4);
    CHECK(view[0][0][3] == 1);
    CHECK(view[0][1][0] == 5);
    CHECK(view[0][1][1] == 9);
    CHECK(view[0][1][2] == 2);
    CHECK(view[0][1][3] == 6);
    CHECK(view[0][2][0] == 5);
    CHECK(view[0][2][1] == 3);
    CHECK(view[0][2][2] == 5);
    CHECK(view[0][2][3] == 8);
    CHECK(view[1][0][0] == 9);
    CHECK(view[1][0][1] == 7);
    CHECK(view[1][0][2] == 9);
    CHECK(view[1][0][3] == 3);
    CHECK(view[1][1][0] == 2);
    CHECK(view[1][1][1] == 3);
    CHECK(view[1][1][2] == 8);
    CHECK(view[1][1][3] == 4);
    CHECK(view[1][2][0] == 6);
    CHECK(view[1][2][1] == 2);
    CHECK(view[1][2][2] == 6);
    CHECK(view[1][2][3] == 4);
}


TEST_CASE(
    "Non-const elements of a vt::ndview can be modified when indexed"
    "[ndarray][view]"
) {
    int data[4] = { 0 };
    const vt::ndview<int, 1> view{{ 4 }, data};

    REQUIRE(view.shape(0) == 4);

    view[0] = 1;
    view[1] = 2;
    view[2] = 3;
    view[3] = 4;

    CHECK(view[0] == 1);
    CHECK(view[1] == 2);
    CHECK(view[2] == 3);
    CHECK(view[3] == 4);
}


TEST_CASE(
    "A vt::ndview<T, N> can convert to a vt::ndview<const T, N>",
    "[ndarray][view]"
) {
    int data[4];
    const vt::ndview<int, 1> view{{ 4 }, data};

    const vt::ndview<const int, 1> cview = view;

    REQUIRE(view.shape() == cview.shape());
    REQUIRE(view.data() == cview.data());
}


TEST_CASE(
    "You can query a vt::ndview's total element count, regardless of "
    "dimensionality",
    "[ndarray][view]"
) {
    const int data[24] = { 0 };
    const vt::ndview<const int, 3> view{{ 4, 3, 2 }, data};

    REQUIRE(view.element_count() == 24);
}


TEST_CASE(
    "You can query a vt::ndview's dimension count",
    "[ndarray][view]"
) {
    const vt::ndview<const int, 12> view{{ 0 }, nullptr};

    REQUIRE(view.dim_count == 12);
}


TEST_CASE(
    "You can reshape a vt::ndview",
    "[ndarray][view]"
) {
    // Explicit integer types for deduction are only required for GCC < 8.0
    constexpr std::size_t n = 3;
    constexpr std::size_t m = 2;

    const int data[6] = {
        3, 1,
        4, 1,
        5, 9
    };
    const vt::ndview<const int, 2> view{{ n, m }, data};

    const vt::ndview<const int, 2> review = view.reshape({ m, n });

    REQUIRE(review.shape(0) == m);
    REQUIRE(review.shape(1) == n);

    CHECK(review[0][0] == 3);
    CHECK(review[0][1] == 1);
    CHECK(review[0][2] == 4);
    CHECK(review[1][0] == 1);
    CHECK(review[1][1] == 5);
    CHECK(review[1][2] == 9);
}


TEST_CASE(
    "You can reshape a vt::ndview to a different number of dimensions",
    "[ndarray][view]"
) {
    const int data[4] = { 3, 1, 4, 1 };
    const vt::ndview<const int, 1> view{{ 4 }, data};

    // Explicit integer types for deduction are only required for GCC < 8.0
    constexpr std::size_t n = 2;
    const vt::ndview<const int, 2> review = view.reshape({ n, n });

    REQUIRE(review.shape(0) == n);
    REQUIRE(review.shape(1) == n);

    CHECK(review[0][0] == 3);
    CHECK(review[0][1] == 1);
    CHECK(review[1][0] == 4);
    CHECK(review[1][1] == 1);
}


TEST_CASE(
    "You can flatten an N-dimensional vt::ndview to a single dimension",
    "[ndarray][view]"
) {
    const int data[8] = {
        3, 1,
        4, 1,

        5, 9,
        2, 6
    };
    const vt::ndview<const int, 3> view{{ 2, 2, 2 }, data};

    const vt::ndview<const int, 1> flat = view.flatten();

    REQUIRE(flat.shape(0) == 8);

    CHECK(flat[0] == 3);
    CHECK(flat[1] == 1);
    CHECK(flat[2] == 4);
    CHECK(flat[3] == 1);
    CHECK(flat[4] == 5);
    CHECK(flat[5] == 9);
    CHECK(flat[6] == 2);
    CHECK(flat[7] == 6);
}


TEST_CASE(
    "You can get a slice-view into a vt::ndview",
    "[ndarray][view]"
) {
    const int data[4] = { 3, 1, 4, 1 };
    const vt::ndview<const int, 1> view{{ 4 }, data};

    const vt::ndview<const int, 1> slice = view.slice(1, 2);

    REQUIRE(slice.shape(0) == 2);

    CHECK(slice[0] == 1);
    CHECK(slice[1] == 4);
}


TEST_CASE(
    "When slicing a vt::ndview with more than 1 dimension, only the first "
    "dimension is sliced",
    "[ndarray][view]"
) {
    const int data[8] = {
        3, 1,
        4, 1,
        5, 9,
        2, 6
    };
    const vt::ndview<const int, 2> view{{ 4, 2 }, data};

    const vt::ndview<const int, 2> slice = view.slice(1, 2);

    REQUIRE(slice.shape(0) == 2);
    REQUIRE(slice.shape(1) == 2);

    CHECK(slice[0][0] == 4);
    CHECK(slice[0][1] == 1);
    CHECK(slice[1][0] == 5);
    CHECK(slice[1][1] == 9);
}


TEST_CASE(
    "When slicing and no count is passed, the last element of the slice will "
    "be the last element of the view",
    "[ndarray][view]"
) {
    const int data[4] = { 3, 1, 4, 1 };
    const vt::ndview<const int, 1> view{{ 4 }, data};

    const vt::ndview<const int, 1> slice = view.slice(1);

    REQUIRE(slice.shape(0) == 3);

    CHECK(slice[0] == 1);
    CHECK(slice[1] == 4);
    CHECK(slice[2] == 1);
}


TEST_CASE(
    "A vt::ndview supports iterating over all elements, regardless of "
    "dimensionality",
    "[ndarray][view]"
) {
    const int data[6] = { 3, 1, 4, 1, 5, 9 };
    const vt::ndview<const int, 2> view{{ 3, 2 }, data};

    REQUIRE(std::equal(view.cbegin(), view.cend(), std::begin(data)));
}


TEST_CASE(
    "Values can also be modified through a vt::ndview's iterators",
    "[ndarray][view]"
) {
    int data[4] = { 0 };
    const vt::ndview<int, 1> view{{ 4 }, data};

    std::iota(view.begin(), view.end(), 0);

    REQUIRE(view.shape(0) == 4);

    CHECK(view[0] == 0);
    CHECK(view[1] == 1);
    CHECK(view[2] == 2);
    CHECK(view[3] == 3);
}


TEST_CASE(
    "A vt::ndview also supports reverse iterators",
    "[ndarray][view]"
) {
    const int data[6] = { 0, 1, 2, 2, 1, 0 };
    const vt::ndview<const int, 1> view{{ 6 }, data};

    REQUIRE(std::equal(view.crbegin(), view.crend(), view.cbegin()));
}


TEST_CASE(
    "Values can also be modified through a vt::ndview's reverse iterators",
    "[ndarray][view]"
) {
    int data[4] = { 0 };
    const vt::ndview<int, 1> view{{ 4 }, data};

    std::iota(view.rbegin(), view.rend(), 0);

    REQUIRE(view.shape(0) == 4);

    CHECK(view[0] == 3);
    CHECK(view[1] == 2);
    CHECK(view[2] == 1);
    CHECK(view[3] == 0);
}


TEST_CASE(
    "A vt::ndview's template arguments can be deduced from its constructor "
    "arguments",
    "[ndarray][view]"
) {
    // Explicit integer types for deduction are only required for GCC < 8.0
    constexpr std::size_t n = 2;

    const int data[n*n] = { 0 };

    vt::ndview view{{ n, n }, data};

    CHECK(std::is_same_v<decltype(view), vt::ndview<const int, 2>>);
}


TEST_CASE(
    "A vt::ndview can be streamed to a std::ostream",
    "[ndarray][view]"
) {
    const int data[4] = {
        1, 0,
        0, 1
    };
    const vt::ndview<const int, 2> view{{ 2, 2 }, data};

    std::ostringstream ss;
    ss << view;

    REQUIRE(ss.str() == "[[1,0],[0,1]]");
}


TEST_CASE(
    "An empty vt::ndview can also be streamed",
    "[ndarray][view]"
) {
    const vt::ndview<const int, 3> view{{ 0 }, nullptr};

    std::ostringstream ss;
    ss << view;

    REQUIRE(ss.str() == "[]");
}
