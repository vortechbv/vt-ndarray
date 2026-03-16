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

#ifndef VT_NDARRAY_INDEX_HPP_
#define VT_NDARRAY_INDEX_HPP_

#include <concepts>
#include <cstddef>
#include <type_traits>


namespace vt {

template<std::size_t N>
struct index_range {};

template<>
struct index_range<1> { std::size_t start; };

template<>
struct index_range<2> { std::size_t start; std::size_t end; };

constexpr index_range<0> r() noexcept;
constexpr index_range<1> r(std::size_t start) noexcept;
constexpr index_range<2> r(std::size_t start, std::size_t end) noexcept;


template<typename T>
concept range_indexer =
    std::is_same_v<T, index_range<0>>
    || std::is_same_v<T, index_range<1>>
    || std::is_same_v<T, index_range<2>>;

template<typename T>
concept indexer = std::convertible_to<T, std::size_t> || range_indexer<T>;


template<std::size_t N, indexer... Index>
struct index_range_count : std::integral_constant<
    std::size_t,
    (N - ((std::convertible_to<Index, std::size_t> ? 1 : 0) + ...))
> {
};

template<std::size_t N, indexer... Index>
constexpr std::size_t index_range_count_v =
    index_range_count<N, Index...>::value;


namespace detail {

template<bool RangeOccured, indexer... Index>
struct is_slice_contiguous : std::true_type {};

template<std::convertible_to<std::size_t> I, indexer... Index>
struct is_slice_contiguous<false, I, Index...>
    : is_slice_contiguous<false, Index...> {
};

template<std::convertible_to<std::size_t> I, indexer... Index>
struct is_slice_contiguous<true, I, Index...> : std::false_type {
};

template<indexer... Index>
struct is_slice_contiguous<true, index_range<1>, Index...> : std::false_type {
};

template<indexer... Index>
struct is_slice_contiguous<true, index_range<2>, Index...> : std::false_type {
};

template<range_indexer R, indexer... Index>
struct is_slice_contiguous<false, R, Index...>
    : is_slice_contiguous<true, Index...> {
};

template<range_indexer R, indexer... Index>
struct is_slice_contiguous<true, R, Index...>
    : is_slice_contiguous<true, Index...> {
};

} // namespace detail

template<indexer... Index>
struct is_slice_contiguous : detail::is_slice_contiguous<false, Index...> {
};

template<indexer... Index>
constexpr bool is_slice_contiguous_v = is_slice_contiguous<Index...>::value;

} // namespace vt


#include <vt/ndarray/impl/index.ipp>

#endif // VT_NDARRAY_INDEX_HPP_
