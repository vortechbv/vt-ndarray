// Copyright (c) 2018 VORtech b.v.
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

#include <vt/ndarray/allocator.hpp>

#include <algorithm>
#include <catch2/catch.hpp>
#include <string>

TEST_CASE(
    "A default constructed vt::ndarray_allocator will align allocation to the "
    "cache line size",
    "[ndarray][allocator]")
{
    const vt::ndarray_allocator<int> alloc;

    REQUIRE(alloc.align_val() == vt::detail::cache_line_size);

    int* p = std::allocator_traits<decltype(alloc)>::allocate(alloc, 4);

    CHECK(std::size_t(p) % alloc.align_val() == 0);

    std::allocator_traits<decltype(alloc)>::deallocate(alloc, p, 4);
}

TEST_CASE(
    "The desired alignment of allocations can be specified when constructing a "
    "vt::ndarray_allocator",
    "[ndarray][allocator]")
{
    const vt::ndarray_allocator<int> alloc{std::align_val_t{8}};

    REQUIRE(alloc.align_val() == 8);

    int* p = std::allocator_traits<decltype(alloc)>::allocate(alloc, 4);

    CHECK(std::size_t(p) % alloc.align_val() == 0);

    std::allocator_traits<decltype(alloc)>::deallocate(alloc, p, 4);
}

TEST_CASE(
    "Allocating from a vt::ndarray_allocator will not return a null pointer",
    "[ndarray][allocator]")
{
    const vt::ndarray_allocator<int> alloc;

    int* p = std::allocator_traits<decltype(alloc)>::allocate(alloc, 4);

    REQUIRE(p != nullptr);

    std::allocator_traits<decltype(alloc)>::deallocate(alloc, p, 4);
}

TEST_CASE(
    "A vt::ndarray_allocator won't default construct fundamental types",
    "[ndarray][allocator]")
{
    const vt::ndarray_allocator<int> alloc;

    int data = 42;

    std::allocator_traits<decltype(alloc)>::construct(alloc, &data);

    CHECK(data == 42);

    std::allocator_traits<decltype(alloc)>::destroy(alloc, &data);
}

TEST_CASE(
    "A vt::ndarray_allocator will default construct non-fundamental types",
    "[ndarray][allocator]")
{
    const vt::ndarray_allocator<std::string> alloc;

    char data[sizeof(std::string)];
    std::fill(std::begin(data), std::end(data), '\xcd');

    auto str = reinterpret_cast<std::string*>(&data);

    std::allocator_traits<decltype(alloc)>::construct(alloc, str);

    CHECK(str->empty());

    std::allocator_traits<decltype(alloc)>::destroy(alloc, str);
}

TEST_CASE(
    "A vt::ndarray_allocator is equal to another vt::ndarray_allocator if "
    "their alignment values are equal, regardless of the value type",
    "[ndarray][allocator]")
{
    const vt::ndarray_allocator<int> alloc;
    const vt::ndarray_allocator<std::string> blloc;

    REQUIRE(alloc == blloc);
}

TEST_CASE(
    "A vt::ndarray_allocator is not equal to another vt::ndarray_allocator if "
    "their alignment values are not equal",
    "[ndarray][allocator]")
{
    const vt::ndarray_allocator<int> alloc{std::align_val_t{8}};
    const vt::ndarray_allocator<std::string> blloc{std::align_val_t{16}};

    REQUIRE(alloc != blloc);
}
