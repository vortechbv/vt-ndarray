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

#ifndef VT_NDARRAY_DETAIL_IMPL_SLICING_IPP_
#define VT_NDARRAY_DETAIL_IMPL_SLICING_IPP_

namespace vt::detail {

template<std::size_t N>
constexpr std::array<std::size_t, N> default_strides(
    const std::array<std::size_t, N>& shape
) noexcept {
    std::array<std::size_t, N> strides;
    for (std::size_t i = 0; i < N; ++i) {
        strides[i] = 1;
        for (std::size_t j = i + 1; j < N; ++j) {
            strides[i] *= shape[j];
        }
    }

    return strides;
}


template<typename T>
constexpr void slice_recursive(
    [[maybe_unused]] const std::size_t* shape,
    [[maybe_unused]] const std::size_t* strides,
    [[maybe_unused]] std::size_t* slice_shape,
    [[maybe_unused]] std::size_t* slice_strides,
    [[maybe_unused]] T*& slice_data
) noexcept {
    // Recursion done
}

template<typename T, indexer... Index>
constexpr void slice_recursive(
    const std::size_t* shape,
    const std::size_t* strides,
    std::size_t* slice_shape,
    std::size_t* slice_strides,
    T*& slice_data,
    [[maybe_unused]] index_range<0> idx,
    Index... idxs
) noexcept {
    slice_shape[0] = shape[0];
    slice_strides[0] = strides[0];

    slice_recursive(
        shape + 1,
        strides + 1,
        slice_shape + 1,
        slice_strides + 1,
        slice_data,
        idxs...
    );
}

template<typename T, indexer... Index>
constexpr void slice_recursive(
    const std::size_t* shape,
    const std::size_t* strides,
    std::size_t* slice_shape,
    std::size_t* slice_strides,
    T*& slice_data,
    index_range<1> idx,
    Index... idxs
) noexcept {
    slice_recursive(
        shape,
        strides,
        slice_shape,
        slice_strides,
        slice_data,
        r(idx.start, shape[0]),
        idxs...
    );
}

template<typename T, indexer... Index>
constexpr void slice_recursive(
    const std::size_t* shape,
    const std::size_t* strides,
    std::size_t* slice_shape,
    std::size_t* slice_strides,
    T*& slice_data,
    index_range<2> idx,
    Index... idxs
) noexcept {
    slice_shape[0] = idx.end - idx.start;
    slice_strides[0] = strides[0];
    slice_data += idx.start * strides[0];

    slice_recursive(
        shape + 1,
        strides + 1,
        slice_shape + 1,
        slice_strides + 1,
        slice_data,
        idxs...
    );
}

template<typename T, indexer... Index>
constexpr void slice_recursive(
    const std::size_t* shape,
    const std::size_t* strides,
    std::size_t* slice_shape,
    std::size_t* slice_strides,
    T*& slice_data,
    std::size_t idx,
    Index... idxs
) noexcept {
    slice_data += idx * strides[0];

    slice_recursive(
        shape + 1,
        strides + 1,
        slice_shape,
        slice_strides,
        slice_data,
        idxs...
    );
}

template<typename T, std::convertible_to<std::size_t> I, indexer... Index>
constexpr void slice_recursive(
    const std::size_t* shape,
    const std::size_t* strides,
    std::size_t* slice_shape,
    std::size_t* slice_strides,
    T*& slice_data,
    I idx,
    Index... idxs
) noexcept {
    slice_recursive(
        shape,
        strides,
        slice_shape,
        slice_strides,
        slice_data,
        std::size_t(idx),
        idxs...
    );
}


template<typename T, std::size_t N, indexer... Index>
constexpr ndslice<T, index_range_count_v<N, Index...>> slice_strided(
    const std::array<std::size_t, N>& shape,
    const std::array<std::size_t, N>& strides,
    T* data,
    Index... idx
) noexcept {
    constexpr std::size_t M = index_range_count_v<N, Index...>;
    std::array<std::size_t, M> slice_shape;
    std::array<std::size_t, M> slice_strides;
    T* slice_data = data;

    slice_recursive(
        shape.data(),
        strides.data(),
        slice_shape.data(),
        slice_strides.data(),
        slice_data,
        idx...
    );

    return ndslice<T, M>{slice_shape, slice_strides, slice_data};
}

template<typename T, std::size_t N, indexer... Index>
constexpr ndview<T, index_range_count_v<N, Index...>> slice_contiguous(
    const std::array<std::size_t, N>& shape,
    T* data,
    Index... idx
) noexcept {
    constexpr std::size_t M = index_range_count_v<N, Index...>;
    const std::array<std::size_t, N> strides = default_strides(shape);
    std::array<std::size_t, M> slice_shape;
    std::array<std::size_t, M> slice_strides;
    T* slice_data = data;

    slice_recursive(
        shape.data(),
        strides.data(),
        slice_shape.data(),
        slice_strides.data(),
        slice_data,
        idx...
    );

    return ndview<T, M>{slice_shape, slice_data};
}

} // namespace vt::detail

#endif // VT_NDARRAY_DETAIL_IMPL_SLICING_IPP_
