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

#ifndef VT_NDARRAY_IMPL_VIEW_IPP_
#define VT_NDARRAY_IMPL_VIEW_IPP_

#include <cassert>
#include <utility>

namespace vt {

namespace detail {

template<std::size_t N>
constexpr std::size_t
count_elements(const std::array<std::size_t, N>& shape) noexcept
{
    // Using a traditional for-loop, since a range-based for-loop or
    // std::accumulate will not get optimized away by all compilers.
    std::size_t count = 1;
    for (std::size_t i = 0; i < N; ++i) {
        count *= shape[i];
    }

    return count;
}

template<std::size_t N, std::size_t... I>
constexpr std::array<std::size_t, N>
to_array_impl(const std::size_t (&shape)[N], std::index_sequence<I...>) noexcept
{
    return { {shape[I]...} };
}

template<std::size_t N>
constexpr std::array<std::size_t, N>
to_array(const std::size_t (&shape)[N]) noexcept
{
    return to_array_impl(shape, std::make_index_sequence<N>{});
}

} // namespace detail

template<typename T, std::size_t N>
constexpr
ndarray_view<T, N>::
ndarray_view(const std::array<std::size_t, N>& shape_, T* data_) noexcept :
    _shape{shape_}, _data{data_}
{
}

template<typename T, std::size_t N>
decltype(auto)
ndarray_view<T, N>::
operator[](std::size_t idx) const noexcept
{
    assert(idx < _shape[0]);

    if constexpr (N > 1) {
        const std::array<std::size_t, N - 1> subshape_ = this->subshape();

        return ndarray_view<T, N - 1>{
            subshape_, _data + idx * detail::count_elements(subshape_)};
    } else {
        return _data[idx];
    }
}

template<typename T, std::size_t N>
constexpr
ndarray_view<T, N>::
operator ndarray_view<const T, N>() const noexcept
{
    return { _shape, _data };
}

template<typename T, std::size_t N>
constexpr std::size_t
ndarray_view<T, N>::
element_count() const noexcept
{
    return detail::count_elements(_shape);
}

template<typename T, std::size_t N>
constexpr const std::array<std::size_t, N>&
ndarray_view<T, N>::
shape() const noexcept
{
    return _shape;
}

template<typename T, std::size_t N>
constexpr std::size_t
ndarray_view<T, N>::
shape(std::size_t dim) const noexcept
{
    assert(dim < N);

    return _shape[dim];
}

template<typename T, std::size_t N>
template<std::size_t M>
constexpr ndarray_view<T, M>
ndarray_view<T, N>::
reshape(const std::array<std::size_t, M>& new_shape) const noexcept
{
    assert(detail::count_elements(new_shape) == this->element_count());

    return { new_shape, this->data() };
}

template<typename T, std::size_t N>
template<std::size_t M>
constexpr ndarray_view<T, M>
ndarray_view<T, N>::
reshape(const std::size_t (&new_shape)[M]) const noexcept
{
    return this->reshape(detail::to_array(new_shape));
}

template<typename T, std::size_t N>
constexpr T*
ndarray_view<T, N>::
data() const noexcept
{
    return _data;
}

template<typename T, std::size_t N>
constexpr vt::ndarray_view<T, N>
ndarray_view<T, N>::
slice(std::size_t offset) const noexcept
{
    return this->slice(offset, _shape[0] - offset);
}

template<typename T, std::size_t N>
constexpr vt::ndarray_view<T, N>
ndarray_view<T, N>::
slice(std::size_t offset, std::size_t count) const noexcept
{
    assert(offset <= _shape[0]);
    assert(offset + count <= _shape[0]);

    if constexpr (N > 1) {
        auto slice_shape = _shape;
        slice_shape[0] = count;
        return vt::ndarray_view<T, N>{
            slice_shape,
            _data + offset * detail::count_elements(this->subshape())};
    } else {
        return vt::ndarray_view<T, 1>{{ count }, _data + offset};
    }
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::iterator
ndarray_view<T, N>::
begin() const noexcept
{
    return _data;
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::const_iterator
ndarray_view<T, N>::
cbegin() const noexcept
{
    return _data;
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::iterator
ndarray_view<T, N>::
end() const noexcept
{
    return _data + this->element_count();
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::const_iterator
ndarray_view<T, N>::
cend() const noexcept
{
    return _data + this->element_count();
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::reverse_iterator
ndarray_view<T, N>::
rbegin() const noexcept
{
    return reverse_iterator{this->end()};
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::const_reverse_iterator
ndarray_view<T, N>::
crbegin() const noexcept
{
    return const_reverse_iterator{this->cend()};
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::reverse_iterator
ndarray_view<T, N>::
rend() const noexcept
{
    return reverse_iterator{this->begin()};
}

template<typename T, std::size_t N>
constexpr typename ndarray_view<T, N>::const_reverse_iterator
ndarray_view<T, N>::
crend() const noexcept
{
    return const_reverse_iterator{this->cbegin()};
}

template<typename T, std::size_t N>
std::array<std::size_t, N - 1>
ndarray_view<T, N>::
subshape() const noexcept
{
    std::array<std::size_t, N - 1> subshape_;
    for (std::size_t i = 0; i < N - 1; ++i) {
        subshape_[i] = _shape[i + 1];
    }

    return subshape_;
}

template<typename T, std::size_t N>
std::ostream&
operator<<(std::ostream& os, ndarray_view<const T, N> a)
{
    const std::size_t n = a.shape(0);

    os << '[';
    if (n > 0) os << a[0];
    for (std::size_t i = 1; i < n; ++i) {
        os << ',' << a[i];
    }
    os << ']';

    return os;
}

} // namespace vt

#endif // VT_NDARRAY_IMPL_VIEW_IPP_
