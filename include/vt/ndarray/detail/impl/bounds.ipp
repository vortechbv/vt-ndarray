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

#ifndef VT_NDARRAY_DETAIL_IMPL_BOUNDS_IPP_
#define VT_NDARRAY_DETAIL_IMPL_BOUNDS_IPP_

namespace vt::detail {

inline constexpr bool is_in_bounds(
    [[maybe_unused]] const std::size_t* shape
) noexcept {
    // Recursion done
    return true;
}

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    [[maybe_unused]] index_range<0> idx,
    Index... idxs
) noexcept {
    return is_in_bounds(shape + 1, idxs...);
}

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    index_range<1> idx,
    Index... idxs
) noexcept {
    return is_in_bounds(shape, r(idx.start, shape[0]), idxs...);
}

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    index_range<2> idx,
    Index... idxs
) noexcept {
    return idx.start <= idx.end
        && idx.end <= shape[0]
        && is_in_bounds(shape + 1, idxs...);
}

template<indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    std::size_t idx,
    Index... idxs
) noexcept {
    return idx < shape[0] && is_in_bounds(shape + 1, idxs...);
}

template<std::convertible_to<std::size_t> I, indexer... Index>
constexpr bool is_in_bounds(
    const std::size_t* shape,
    I idx,
    Index... idxs
) noexcept {
    return is_in_bounds(shape, std::size_t(idx), idxs...);
}

} // namespace vt::detail

#endif // VT_NDARRAY_DETAIL_IMPL_BOUNDS_IPP_
