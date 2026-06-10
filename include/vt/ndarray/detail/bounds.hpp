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

#ifndef VT_NDARRAY_DETAIL_BOUNDS_HPP_
#define VT_NDARRAY_DETAIL_BOUNDS_HPP_

#include <vt/ndarray/index.hpp>

#include <concepts>
#include <cstddef>


namespace vt::detail {

constexpr bool is_in_bounds(const std::size_t* shape) noexcept;

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    index_range<0> idx,
    Index... idxs
) noexcept;

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    index_range<1> idx,
    Index... idxs
) noexcept;

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    index_range<2> idx,
    Index... idxs
) noexcept;

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    std::size_t idx,
    Index... idxs
) noexcept;

template<std::convertible_to<std::size_t> I, indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    I idx,
    Index... idxs
) noexcept;

} // namespace vt::detail


#include <vt/ndarray/detail/impl/bounds.ipp>

#endif // VT_NDARRAY_DETAIL_BOUNDS_HPP_
