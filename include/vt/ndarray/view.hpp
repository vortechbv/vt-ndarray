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

#ifndef VT_NDARRAY_VIEW_HPP_
#define VT_NDARRAY_VIEW_HPP_

#include <array>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <type_traits>


namespace vt {

template<typename T, std::size_t N>
class ndview {
    static_assert(N > 0);

public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using index_type = std::size_t;
    using pointer = T*;
    using reference = T&;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr std::size_t dim_count = N;

    constexpr ndview(
        const std::array<std::size_t, N>& shape_,
        T* data_
    ) noexcept;

    decltype(auto) operator[](std::size_t idx) const noexcept;

    constexpr operator ndview<const T, N>() const noexcept;

    constexpr std::size_t element_count() const noexcept;

    constexpr const std::array<std::size_t, N>& shape() const noexcept;
    constexpr std::size_t shape(std::size_t dim) const noexcept;

    template<std::size_t M>
    constexpr ndview<T, M> reshape(
        const std::array<std::size_t, M>& new_shape
    ) const noexcept;
    template<std::size_t M>
    constexpr ndview<T, M> reshape(
        const std::size_t (&new_shape)[M]
    ) const noexcept;

    constexpr ndview<T, 1> flatten() const noexcept;

    constexpr T* data() const noexcept;

    constexpr ndview<T, N> slice(std::size_t offset) const noexcept;
    constexpr ndview<T, N> slice(
        std::size_t offset,
        std::size_t count
    ) const noexcept;

    constexpr iterator begin() const noexcept;
    constexpr const_iterator cbegin() const noexcept;

    constexpr iterator end() const noexcept;
    constexpr const_iterator cend() const noexcept;

    constexpr reverse_iterator rbegin() const noexcept;
    constexpr const_reverse_iterator crbegin() const noexcept;

    constexpr reverse_iterator rend() const noexcept;
    constexpr const_reverse_iterator crend() const noexcept;

private:
    std::array<std::size_t, N> _shape;
    T* _data;

    std::array<std::size_t, N - 1> subshape() const noexcept;
};


template<typename T, std::size_t N>
using ndarray_view = ndview<T, N>;

template<typename T, std::size_t N>
ndview(const std::size_t (&)[N], T*) -> ndview<T, N>;

template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, ndview<const T, N> a);

} // namespace vt

#include <vt/ndarray/impl/view.ipp>

#endif // VT_NDARRAY_VIEW_HPP_
