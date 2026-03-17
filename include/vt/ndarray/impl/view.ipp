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

#ifndef VT_NDARRAY_IMPL_VIEW_IPP_
#define VT_NDARRAY_IMPL_VIEW_IPP_

#include <vt/ndarray/detail/bounds.hpp>
#include <vt/ndarray/detail/indexing.hpp>
#include <vt/ndarray/detail/slicing.hpp>

#include <cassert>
#include <utility>


namespace vt {

template<typename T, std::size_t N>
constexpr ndview<T, N>::ndview(
    const std::array<std::size_t, N>& shape_,
    T* data_
) noexcept :
    _shape{shape_},
    _data{data_}
{
}


template<typename T, std::size_t N>
template<indexer... Index>
constexpr decltype(auto) ndview<T, N>::operator[](
    Index... idx
) const noexcept requires((sizeof...(Index) <= N)) {
    if constexpr (sizeof...(Index) == N) {
        assert(detail::is_in_bounds(_shape.data(), idx...));
        if constexpr ((std::convertible_to<Index, std::size_t> && ...)) {
            return _data[detail::index_contiguous(_shape.data(), idx...)];
        } else if constexpr (is_slice_contiguous_v<Index...>) {
            return detail::slice_contiguous(_shape, _data, idx...);
        } else {
            const auto strides = detail::default_strides(_shape);
            return detail::slice_strided(_shape, strides, _data, idx...);
        }
    } else {
        return detail::pad_index_call(*this, idx...);
    }
}


template<typename T, std::size_t N>
constexpr ndview<T, N>::operator ndview<const T, N>() const noexcept {
    return { _shape, _data };
}


template<typename T, std::size_t N>
constexpr std::size_t ndview<T, N>::element_count() const noexcept {
    return detail::product(_shape);
}


template<typename T, std::size_t N>
constexpr const std::array<std::size_t, N>& ndview<T, N>::shape(
) const noexcept {
    return _shape;
}


template<typename T, std::size_t N>
constexpr std::size_t ndview<T, N>::shape(std::size_t dim) const noexcept {
    assert(dim < N);

    return _shape[dim];
}


template<typename T, std::size_t N>
template<std::size_t M>
constexpr ndview<T, M> ndview<T, N>::reshape(
    const std::array<std::size_t, M>& new_shape
) const noexcept {
    assert(detail::product(new_shape) == this->element_count());

    return { new_shape, this->data() };
}


template<typename T, std::size_t N>
template<std::size_t M>
constexpr ndview<T, M> ndview<T, N>::reshape(
    const std::size_t (&new_shape)[M]
) const noexcept {
    return this->reshape(std::to_array(new_shape));
}


template<typename T, std::size_t N>
constexpr ndview<T, 1> ndview<T, N>::flatten() const noexcept {
    return { { this->element_count() }, this->data() };
}


template<typename T, std::size_t N>
constexpr T* ndview<T, N>::data() const noexcept {
    return _data;
}


template<typename T, std::size_t N>
constexpr ndview<T, N> ndview<T, N>::slice(std::size_t offset) const noexcept {
    return this->slice(offset, _shape[0] - offset);
}


template<typename T, std::size_t N>
constexpr ndview<T, N>
ndview<T, N>::slice(std::size_t offset, std::size_t count) const noexcept {
    return this->operator[](r(offset, offset + count));
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::iterator ndview<T, N>::begin() const noexcept {
    return _data;
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::const_iterator ndview<T, N>::cbegin(
) const noexcept {
    return _data;
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::iterator ndview<T, N>::end() const noexcept {
    return _data + this->element_count();
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::const_iterator ndview<T, N>::cend(
) const noexcept {
    return _data + this->element_count();
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::reverse_iterator ndview<T, N>::rbegin(
) const noexcept {
    return reverse_iterator{this->end()};
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::const_reverse_iterator ndview<T, N>::crbegin(
) const noexcept {
    return const_reverse_iterator{this->cend()};
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::reverse_iterator ndview<T, N>::rend(
) const noexcept {
    return reverse_iterator{this->begin()};
}


template<typename T, std::size_t N>
constexpr typename ndview<T, N>::const_reverse_iterator ndview<T, N>::crend(
) const noexcept {
    return const_reverse_iterator{this->cbegin()};
}


template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, ndview<const T, N> a) {
    const std::size_t n = a.shape(0);

    os << '[';
    if (n > 0) os << a[0];
    for (std::size_t i = 1; i < n; ++i) {
        os << ',' << a[i];
    }
    os << ']';

    return os;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N>::ndslice_iterator() noexcept :
    ndslice_iterator{std::size_t(-1), {}, {}, nullptr}
{
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N>::ndslice_iterator(
    std::size_t start,
    const std::array<std::size_t, N>& shape_,
    const std::array<std::size_t, N>& strides_,
    T* data_
) noexcept :
    _iter{start},
    _shape{shape_},
    _strides{strides_},
    _data{data_}
{
}


template<typename T, std::size_t N>
constexpr T& ndslice_iterator<T, N>::operator[](
    std::size_t idx
) const noexcept {
    return this->index(idx, std::make_index_sequence<N>{});
}


template<typename T, std::size_t N>
constexpr T& ndslice_iterator<T, N>::operator*() const noexcept {
    return this->operator[](_iter);
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N>& ndslice_iterator<T, N>::operator++(
) noexcept {
    ++_iter;
    return *this;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N> ndslice_iterator<T, N>::operator++(
    int
) noexcept {
    const auto copy = *this;
    ++_iter;
    return copy;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N>& ndslice_iterator<T, N>::operator--(
) noexcept {
    --_iter;
    return *this;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N> ndslice_iterator<T, N>::operator--(
    int
) noexcept {
    const auto copy = *this;
    --_iter;
    return copy;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N>& ndslice_iterator<T, N>::operator+=(
    difference_type diff
) noexcept {
    _iter += diff;
    return *this;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N> ndslice_iterator<T, N>::operator+(
    difference_type diff
) const noexcept {
    const auto copy = *this;
    copy += diff;
    return copy;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N>& ndslice_iterator<T, N>::operator-=(
    difference_type diff
) noexcept {
    _iter -= diff;
    return *this;
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N> ndslice_iterator<T, N>::operator-(
    difference_type diff
) const noexcept {
    const auto copy = *this;
    copy -= diff;
    return copy;
}


template<typename T, std::size_t N>
constexpr typename ndslice_iterator<T, N>::difference_type
ndslice_iterator<T, N>::operator-(
    const ndslice_iterator<T, N>& other
) const noexcept {
    return _iter - other._iter;
}


template<typename T, std::size_t N>
constexpr auto ndslice_iterator<T, N>::operator<=>(
    const ndslice_iterator<T, N>& other
) const noexcept {
    return _iter <=> other._iter;
}


template<typename T, std::size_t N>
constexpr bool ndslice_iterator<T, N>::operator==(
    const ndslice_iterator<T, N>& other
) const noexcept {
    return _iter == other._iter;
}


template<typename T, std::size_t N>
template<std::size_t... I>
constexpr T& ndslice_iterator<T, N>::index(
    std::size_t idx,
    std::index_sequence<I...>
) const noexcept {
    const std::size_t offset = detail::index_strided(
        _strides.data(),
        detail::iter2indices<N, I>(idx, _shape.data())...
    );
    return _data[offset];
}


template<typename T, std::size_t N>
constexpr ndslice_iterator<T, N> operator+(
    typename ndslice_iterator<T, N>::difference_type a,
    const ndslice_iterator<T, N>& b
) noexcept {
    return b + a;
}


template<typename T, std::size_t N>
constexpr ndslice<T, N>::ndslice(
    const std::array<std::size_t, N>& shape_,
    T* data_
) noexcept :
    ndslice{shape_, detail::default_strides(shape_), data_}
{
}

template<typename T, std::size_t N>
constexpr ndslice<T, N>::ndslice(
    const std::array<std::size_t, N>& shape_,
    const std::array<std::size_t, N>& strides_,
    T* data_
) noexcept :
    _strides{strides_},
    _data{data_},
    _shape{shape_}
{
}


template<typename T, std::size_t N>
constexpr ndslice<T, N>::ndslice(const ndview<T, N>& view) noexcept :
    ndslice{view.shape(), view.data()}
{
}


template<typename T, std::size_t N>
constexpr ndslice<T, N>::ndslice(
    const ndview<std::remove_const_t<T>, N>& view
) noexcept requires(std::is_const_v<T>) :
    ndslice{view.shape(), view.data()}
{
}


template<typename T, std::size_t N>
template<indexer... Index>
constexpr decltype(auto) ndslice<T, N>::operator[](
    Index... idx
) const noexcept requires((sizeof...(Index) <= N)) {
    if constexpr (sizeof...(Index) == N) {
        assert(detail::is_in_bounds(_shape.data(), idx...));
        if constexpr ((std::convertible_to<Index, std::size_t> && ...)) {
            return _data[detail::index_strided(_strides.data(), idx...)];
        } else {
            return detail::slice_strided(_shape, _strides, _data, idx...);
        }
    } else {
        return detail::pad_index_call(*this, idx...);
    }
}


template<typename T, std::size_t N>
constexpr ndslice<T, N>::operator ndslice<const T, N>() const noexcept {
    return { _shape, _strides, _data };
}


template<typename T, std::size_t N>
constexpr std::size_t ndslice<T, N>::element_count() const noexcept {
    return detail::product(_shape);
}


template<typename T, std::size_t N>
constexpr const std::array<std::size_t, N>& ndslice<T, N>::shape(
) const noexcept {
    return _shape;
}


template<typename T, std::size_t N>
constexpr std::size_t ndslice<T, N>::shape(std::size_t dim) const noexcept {
    assert(dim < N);

    return _shape[dim];
}


template<typename T, std::size_t N>
constexpr const std::array<std::size_t, N>& ndslice<T, N>::strides(
) const noexcept {
    return _strides;
}


template<typename T, std::size_t N>
constexpr std::size_t ndslice<T, N>::strides(std::size_t dim) const noexcept {
    assert(dim < N);

    return _strides[dim];
}


template<typename T, std::size_t N>
constexpr T* ndslice<T, N>::data() const noexcept {
    return _data;
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::iterator ndslice<T, N>::begin() const noexcept {
    return iterator{0, _shape, _strides, _data};
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::const_iterator ndslice<T, N>::cbegin(
) const noexcept {
    return const_iterator{0, _shape, _strides, _data};
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::iterator ndslice<T, N>::end() const noexcept {
    return iterator{this->element_count(), _shape, _strides, _data};
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::const_iterator ndslice<T, N>::cend(
) const noexcept {
    return const_iterator{this->element_count(), _shape, _strides, _data};
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::reverse_iterator ndslice<T, N>::rbegin(
) const noexcept {
    return reverse_iterator{this->end()};
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::const_reverse_iterator ndslice<T, N>::crbegin(
) const noexcept {
    return const_reverse_iterator{this->cend()};
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::reverse_iterator ndslice<T, N>::rend(
) const noexcept {
    return reverse_iterator{this->begin()};
}


template<typename T, std::size_t N>
constexpr typename ndslice<T, N>::const_reverse_iterator ndslice<T, N>::crend(
) const noexcept {
    return const_reverse_iterator{this->cbegin()};
}


template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, ndslice<const T, N> a) {
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
