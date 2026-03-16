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

#ifndef VT_NDARRAY_DETAIL_INDEXING_HPP_
#define VT_NDARRAY_DETAIL_INDEXING_HPP_

#include <vt/ndarray/index.hpp>

#include <array>
#include <concepts>
#include <cstddef>
#include <utility>


namespace vt::detail {

template<std::size_t... I>
constexpr std::size_t product(
    const std::size_t* shape,
    std::index_sequence<I...>
) noexcept;

template<std::size_t N>
constexpr std::size_t product(const std::size_t* shape) noexcept;

template<std::size_t N>
constexpr std::size_t product(const std::array<std::size_t, N>& shape) noexcept;


constexpr std::size_t index_contiguous(
    const std::size_t* shape,
    std::size_t idx
) noexcept;

template<std::same_as<std::size_t>... Index>
constexpr std::size_t index_contiguous(
    const std::size_t* shape,
    std::size_t idx,
    Index... idxs
) noexcept;

template<std::convertible_to<std::size_t>... Index>
constexpr std::size_t index_contiguous(
    const std::size_t* shape,
    Index... idxs
) noexcept;


constexpr std::size_t index_strided(
    const std::size_t* strides,
    std::size_t idx
) noexcept;

template<std::same_as<std::size_t>... Index>
constexpr std::size_t index_strided(
    const std::size_t* strides,
    std::size_t idx,
    Index... idxs
) noexcept;

template<std::convertible_to<std::size_t>... Index>
constexpr std::size_t index_strided(
    const std::size_t* strides,
    Index... idxs
) noexcept;


// Utility for padding instances of index_range<0> when the caller specifies
// less indices than the number of dimensions.

template<std::size_t>
using pad_indexer = index_range<0>;

template<typename T, std::size_t... I, indexer... Index>
constexpr decltype(auto) pad_index_call_impl(
    const T& indexee,
    std::index_sequence<I...>,
    Index... idx
) noexcept;

template<typename T, indexer... Index>
constexpr decltype(auto) pad_index_call(
    const T& indexee,
    Index... idx
) noexcept;

} // namespace vt::detail


#include <vt/ndarray/detail/impl/indexing.ipp>

#endif // VT_NDARRAY_DETAIL_INDEXING_HPP_
