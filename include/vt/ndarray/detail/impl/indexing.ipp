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

#ifndef VT_NDARRAY_DETAIL_IMPL_INDEXING_IPP_
#define VT_NDARRAY_DETAIL_IMPL_INDEXING_IPP_

namespace vt::detail {

template<std::size_t... I>
constexpr std::size_t product(
    const std::size_t* shape,
    std::index_sequence<I...>
) noexcept {
    return (shape[I] * ...);
}

template<std::size_t N>
constexpr std::size_t product(const std::size_t* shape) noexcept {
    return product(shape, std::make_index_sequence<N>{});
}

template<std::size_t N>
constexpr std::size_t product(
    const std::array<std::size_t, N>& shape
) noexcept {
    return product<N>(shape.data());
}


inline constexpr std::size_t index_contiguous(
    [[maybe_unused]] const std::size_t* shape,
    std::size_t idx
) noexcept {
    return idx;
}

template<std::same_as<std::size_t>... Index>
constexpr std::size_t index_contiguous(
    const std::size_t* shape,
    std::size_t idx,
    Index... idxs
) noexcept {
    constexpr std::size_t M = sizeof...(Index);
    return idx * product<M>(shape + 1) + index_contiguous(shape + 1, idxs...);
}

template<std::convertible_to<std::size_t>... Index>
constexpr std::size_t index_contiguous(
    const std::size_t* shape,
    Index... idxs
) noexcept {
    return index_contiguous(shape, std::size_t(idxs)...);
}


inline constexpr std::size_t index_strided(
    const std::size_t* strides,
    std::size_t idx
) noexcept {
    return idx * strides[0];
}

template<std::same_as<std::size_t>... Index>
constexpr std::size_t index_strided(
    const std::size_t* strides,
    std::size_t idx,
    Index... idxs
) noexcept {
    return idx * strides[0] + index_strided(strides + 1, idxs...);
}

template<std::convertible_to<std::size_t>... Index>
constexpr std::size_t index_strided(
    const std::size_t* strides,
    Index... idxs
) noexcept {
    return index_strided(strides, std::size_t(idxs)...);
}


template<typename T, std::size_t... I, indexer... Index>
constexpr decltype(auto) pad_index_call_impl(
    const T& indexee,
    std::index_sequence<I...>,
    Index... idx
) noexcept {
    return indexee[idx..., pad_indexer<I>{}...];
}

template<typename T, indexer... Index>
constexpr decltype(auto) pad_index_call(
    const T& indexee,
    Index... idx
) noexcept {
    return pad_index_call_impl(
        indexee,
        std::make_index_sequence<T::dim_count - sizeof...(Index)>{},
        idx...
    );
}

} // namespace vt::detail

#endif // VT_NDARRAY_DETAIL_IMPL_INDEXING_IPP_
