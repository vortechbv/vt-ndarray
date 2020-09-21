// Copyright (c) 2017-2020 VORtech b.v.
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

#include <vt/ndarray/container.hpp>

#include <algorithm>
#include <catch2/catch.hpp>
#include <numeric>

TEST_CASE(
    "An empty vt::ndarray can be default constructed without any allocations",
    "[ndarray][container]")
{
    const vt::ndarray<int, 1> a;

    REQUIRE(a.shape(0) == 0);
    REQUIRE(a.data() == nullptr);
}

TEST_CASE(
    "A vt::ndarray can be constructed with a user specified allocator",
    "[ndarray][container]")
{
    vt::ndarray_allocator<int> alloc{std::align_val_t{16}};
    const vt::ndarray<int, 1> a{alloc};

    REQUIRE(a.get_allocator() == alloc);
}

TEST_CASE(
    "A vt::ndarray can be constructed with a shape without zero-initializing",
    "[ndarray][container]")
{
    const vt::ndarray<int, 2> a{{ 2, 3 }};

    REQUIRE(a.shape(0) == 2);
    REQUIRE(a.shape(1) == 3);
    REQUIRE(a.data() != nullptr);
}

TEST_CASE(
    "A vt::ndarray of non-trivial types will still have its elements default "
    "constructed",
    "[ndarray][container]")
{
    const vt::ndarray<std::string, 1> a{{ 4 }};

    REQUIRE(a.shape(0) == 4);

    CHECK(a[0].empty());
    CHECK(a[1].empty());
    CHECK(a[2].empty());
    CHECK(a[3].empty());
}

TEST_CASE(
    "A vt::ndarray with std::allocator as allocator will still zero-initialize",
    "[ndarray][container]")
{
    const vt::ndarray<int, 1, std::allocator<int>> a{{ 4 }};

    REQUIRE(a.shape(0) == 4);

    CHECK(a[0] == 0);
    CHECK(a[1] == 0);
    CHECK(a[2] == 0);
    CHECK(a[3] == 0);
}

TEST_CASE(
    "A vt::ndarray can be constructed with a default value",
    "[ndarray][container]")
{
    const vt::ndarray<int, 1> a{{ 4 }, 42};

    REQUIRE(a.shape(0) == 4);

    CHECK(a[0] == 42);
    CHECK(a[1] == 42);
    CHECK(a[2] == 42);
    CHECK(a[3] == 42);
}

TEST_CASE(
    "A vt::ndarray can be constructed with a default value of non-trivial type",
    "[ndarray][container]")
{
    const vt::ndarray<std::string, 1> a{{ 4 }, "42"};

    REQUIRE(a.shape(0) == 4);

    CHECK(a[0] == "42");
    CHECK(a[1] == "42");
    CHECK(a[2] == "42");
    CHECK(a[3] == "42");
}

TEST_CASE(
    "A vt::ndarray can be constructed with an iterator range",
    "[ndarray][container]")
{
    const int a[6] = {
        3, 1, 4,
        1, 5, 9
    };

    const vt::ndarray<int, 2> b{{ 2, 3 }, std::begin(a), std::end(a)};

    REQUIRE(b.shape(0) == 2);
    REQUIRE(b.shape(1) == 3);

    CHECK(b[0][0] == 3);
    CHECK(b[0][1] == 1);
    CHECK(b[0][2] == 4);
    CHECK(b[1][0] == 1);
    CHECK(b[1][1] == 5);
    CHECK(b[1][2] == 9);
}

TEST_CASE(
    "A vt::ndarray can be constructed with an iterator range of non-trivial "
    "types",
    "[ndarray][container]")
{
    const std::string a[3] = { "31", "41", "59" };

    const vt::ndarray<std::string, 1> b{{ 3 }, std::begin(a), std::end(a)};

    REQUIRE(b.shape(0) == 3);

    CHECK(b[0] == "31");
    CHECK(b[1] == "41");
    CHECK(b[2] == "59");
}

struct except_on_copy {
    static thread_local unsigned count;

    except_on_copy()
    {
        ++count;
    }

    except_on_copy(const except_on_copy&)
    {
        if (count >= 6) throw std::exception{};
        ++count;
    }

    ~except_on_copy()
    {
        --count;
    }
};

thread_local unsigned except_on_copy::count = 0;

TEST_CASE(
    "If an exception occurs while copying elements into a vt::ndarray, all "
    "already constructed elements will be destructed",
    "[ndarray][container]")
{
    const except_on_copy a[4];

    REQUIRE(except_on_copy::count == 4);

    REQUIRE_THROWS(
        vt::ndarray<except_on_copy, 1>{{ 4 }, std::begin(a), std::end(a)});

    REQUIRE(except_on_copy::count == 4);
}

TEST_CASE(
    "A vt::ndarray can be constructed from an initializer list",
    "[ndarray][container]")
{
    const vt::ndarray<int, 2> a{{ 2, 3 }, {
        3, 1, 4,
        1, 5, 9
    }};

    REQUIRE(a.shape(0) == 2);
    REQUIRE(a.shape(1) == 3);

    CHECK(a[0][0] == 3);
    CHECK(a[0][1] == 1);
    CHECK(a[0][2] == 4);
    CHECK(a[1][0] == 1);
    CHECK(a[1][1] == 5);
    CHECK(a[1][2] == 9);
}

TEST_CASE(
    "A vt::ndarray can be copy-constructed",
    "[ndarray][container]")
{
    const vt::ndarray<int, 1> a{{ 4 }, { 3, 1, 4, 1 }};

    const vt::ndarray<int, 1> b = a;

    REQUIRE(a == b);
}

TEST_CASE(
    "A vt::ndarray can be move-constructed",
    "[ndarray][container]")
{
    vt::ndarray<int, 1> a{{ 4 }, { 3, 1, 4, 1 }};

    const vt::ndarray<int, 1> b = std::move(a);

    REQUIRE(a.shape(0) == 0);
    REQUIRE(a.data() == nullptr);

    REQUIRE(b.shape(0) == 4);

    CHECK(b[0] == 3);
    CHECK(b[1] == 1);
    CHECK(b[2] == 4);
    CHECK(b[3] == 1);
}

TEST_CASE(
    "A vt::ndarray can be copy-assigned",
    "[ndarray][container]")
{
    vt::ndarray<int, 1> a;
    const vt::ndarray<int, 1> b{{ 4 }, { 3, 1, 4, 1 }};

    a = b;

    REQUIRE(a == b);
}

TEST_CASE(
    "A vt::ndarray copy-assign does not reallocate if the element count is "
    "equal",
    "[ndarray][container]")
{
    vt::ndarray<int, 2> a{{ 3, 2 }};
    const vt::ndarray<int, 2> b{{ 2, 3 }, {
        3, 1, 4,
        1, 5, 9
    }};

    const int* const prev_a_data = a.data();

    a = b;

    REQUIRE(a.data() == prev_a_data);
    REQUIRE(a == b);
}

TEST_CASE(
    "A self-copy-assign of a vt::ndarray is a no-op",
    "[ndarray][container")
{
    vt::ndarray<int, 1> a{{ 4 }, { 3, 1, 4, 1 }};

    a = a;

    REQUIRE(a.shape(0) == 4);

    CHECK(a[0] == 3);
    CHECK(a[1] == 1);
    CHECK(a[2] == 4);
    CHECK(a[3] == 1);
}

TEST_CASE(
    "A vt::ndarray can be move-assigned",
    "[ndarray][container]")
{
    vt::ndarray<int, 1> a;
    vt::ndarray<int, 1> b{{ 4 }, { 3, 1, 4, 1 }};

    a = std::move(b);

    REQUIRE(b.shape(0) == 0);
    REQUIRE(b.data() == nullptr);

    REQUIRE(a.shape(0) == 4);

    CHECK(a[0] == 3);
    CHECK(a[1] == 1);
    CHECK(a[2] == 4);
    CHECK(a[3] == 1);
}

TEST_CASE(
    "A self-move-assign of a vt::ndarray is a no-op",
    "[ndarray][container")
{
    vt::ndarray<int, 1> a{{ 4 }, { 3, 1, 4, 1 }};

    a = std::move(a);

    REQUIRE(a.shape(0) == 4);

    CHECK(a[0] == 3);
    CHECK(a[1] == 1);
    CHECK(a[2] == 4);
    CHECK(a[3] == 1);
}

TEST_CASE(
    "A non-const vt::ndarray can be modified through its operator[]",
    "[ndarray][container]")
{
    vt::ndarray<int, 2> a{{ 2, 3 }};

    REQUIRE(a.shape(0) == 2);
    REQUIRE(a.shape(1) == 3);

    a[0][0] = 0;
    a[0][1] = 1;
    a[0][2] = 2;
    a[1][0] = 3;
    a[1][1] = 4;
    a[1][2] = 5;

    CHECK(a[0][0] == 0);
    CHECK(a[0][1] == 1);
    CHECK(a[0][2] == 2);
    CHECK(a[1][0] == 3);
    CHECK(a[1][1] == 4);
    CHECK(a[1][2] == 5);
}

TEST_CASE(
    "You can get a slice view into a vt::ndarray",
    "[ndarray][container]")
{
    const vt::ndarray<int, 2> a{{ 4, 2 }, {
        3, 1,
        4, 1,
        5, 9,
        2, 6
    }};

    const vt::ndarray_view<const int, 2> slice = a.slice(1, 2);

    REQUIRE(slice.shape(0) == 2);
    REQUIRE(slice.shape(1) == 2);

    CHECK(slice[0][0] == 4);
    CHECK(slice[0][1] == 1);
    CHECK(slice[1][0] == 5);
    CHECK(slice[1][1] == 9);
}

#if __has_include(<memory_resource>)

TEST_CASE(
    "A vt::pmr::ndarray can be constructed with a polymorphic allocator",
    "[ndarray][container]")
{
    int buffer[6];
    std::pmr::monotonic_buffer_resource arena{buffer, sizeof(buffer)};

    const vt::pmr::ndarray<int, 2> a{{ 2, 3 }, &arena};

    CHECK(buffer == a.data());
}

#endif // __has_include(<memory_resource>)

TEST_CASE(
    "A vt::ndarray is equality comparable",
    "[ndarray][container]")
{
    const vt::ndarray<int, 1> a{{ 4 }, { 3, 1, 4, 1 }};
    const vt::ndarray<int, 1> b{{ 4 }, { 3, 1, 4, 1 }};

    REQUIRE(a == b);
}

TEST_CASE(
    "A vt::ndarray is inequality comparable",
    "[ndarray][container]")
{
    const vt::ndarray<int, 1> a{{ 4 }, { 3, 1, 4, 1 }};
    const vt::ndarray<int, 1> b{{ 4 }, { 3, 1, 4, 2 }};

    REQUIRE(a != b);
}

TEST_CASE(
    "If the shape doesn't match, a vt::ndarray is never equal",
    "[ndarray][container]")
{
    const vt::ndarray<int, 2> a{{ 2, 3 }, {
        3, 1, 4,
        1, 5, 9
    }};
    const vt::ndarray<int, 2> b{{ 3, 2 }, {
        3, 1,
        4, 1,
        5, 9
    }};

    REQUIRE(a != b);
}

TEST_CASE(
    "A vt::ndarray is swappable",
    "[ndarray][container]")
{
    vt::ndarray<int, 1> a{{ 4 }, { 3, 1, 4, 1 }};
    vt::ndarray<int, 1> b{{ 3 }, { 0, 1, 2 }};

    swap(a, b);

    REQUIRE(a.shape(0) == 3);

    CHECK(a[0] == 0);
    CHECK(a[1] == 1);
    CHECK(a[2] == 2);

    REQUIRE(b.shape(0) == 4);

    CHECK(b[0] == 3);
    CHECK(b[1] == 1);
    CHECK(b[2] == 4);
    CHECK(b[3] == 1);
}
