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

#ifndef VT_NDARRAY_IMPL_CONTAINER_IPP_
#define VT_NDARRAY_IMPL_CONTAINER_IPP_

#include <algorithm>
#include <cassert>

namespace vt {

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray() noexcept(noexcept(Allocator{})) :
    ndarray{Allocator{}}
{
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(const Allocator& alloc) noexcept :
    _alloc{alloc},
    _view{{ 0 }, nullptr}
{
    static_assert(std::is_nothrow_copy_constructible_v<Allocator>);
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(const std::array<std::size_t, N>& shape_, const Allocator& alloc) :
    _alloc{alloc},
    _view{this->make_allocated_view(shape_)}
{
    static_assert(std::is_default_constructible_v<T>);

    if constexpr (std::is_nothrow_default_constructible_v<T>) {
        for (auto& el : *this) {
            std::allocator_traits<Allocator>::construct(_alloc, &el);
        }
    } else {
        auto it = this->begin();
        try {
            auto end_ = this->end();
            for (; it != end_; ++it) {
                std::allocator_traits<Allocator>::construct(_alloc, it);
            }
        } catch (...) {
            this->destroy(this->begin(), it);
            throw;
        }
    }
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(
    const std::array<std::size_t, N>& shape_, const T& init,
    const Allocator& alloc)
:
    _alloc{alloc},
    _view{this->make_allocated_view(shape_)}
{
    static_assert(std::is_copy_constructible_v<T>);

    if constexpr (std::is_nothrow_copy_constructible_v<T>) {
        for (auto& el : *this) {
            std::allocator_traits<Allocator>::construct(_alloc, &el, init);
        }
    } else {
        auto it = this->begin();
        try {
            auto end_ = this->end();
            for (; it != end_; ++it) {
                std::allocator_traits<Allocator>::construct(_alloc, it, init);
            }
        } catch (...) {
            this->destroy(this->begin(), it);
            throw;
        }
    }
}

template<typename T, std::size_t N, typename Allocator>
template<typename InputIt>
ndarray<T, N, Allocator>::
ndarray(
    const std::array<std::size_t, N>& shape_,
    InputIt first, InputIt last,
    const Allocator& alloc)
:
    _alloc{alloc},
    _view{this->make_allocated_view(shape_)}
{
    this->copy_construct(first, last);
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(
    const std::array<std::size_t, N>& shape_,
    std::initializer_list<T> init,
    const Allocator& alloc)
:
    ndarray{shape_, init.begin(), init.end(), alloc}
{
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(const ndarray& other) :
    ndarray{
        other.shape(), other.begin(), other.end(),
        std::allocator_traits<Allocator>::
            select_on_container_copy_construction(other._alloc)}
{
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(const ndarray& other, const Allocator& alloc) :
    ndarray{other.shape(), other.begin(), other.end(), alloc}
{
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(ndarray&& other) noexcept :
    _alloc{std::move(other._alloc)},
    _view{std::exchange(other._view, { { 0 }, nullptr })}
{
    static_assert(std::is_nothrow_move_constructible_v<Allocator>);
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
ndarray(ndarray&& other, const Allocator& alloc) :
    _alloc{alloc}
{
    if (_alloc == other._alloc) {
        _view = std::exchange(other._view, { { 0 }, nullptr });
    } else {
        _view = this->make_allocated_view(other.shape());

        this->move_construct(other.begin(), other.end());
    }
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
~ndarray()
{
    this->destroy();
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>&
ndarray<T, N, Allocator>::
operator=(const ndarray& other)
{
    if (&other == this) return *this;

    constexpr bool should_copy_alloc = std::allocator_traits<Allocator>::
        propagate_on_container_copy_assignment::value;
    const bool should_realloc =
        (should_copy_alloc && _alloc != other._alloc) ||
        this->element_count() != other.element_count();

    if (should_realloc) {
        this->destroy();
        _view = { { 0 }, nullptr };

        if constexpr (should_copy_alloc) _alloc = other._alloc;
        _view = this->make_allocated_view(other.shape());

        this->copy_construct(other.begin(), other.end());
    } else {
        if constexpr (should_copy_alloc) _alloc = other._alloc;
        _view = { other.shape(), this->data() };
        std::copy(other.begin(), other.end(), this->begin());
    }

    return *this;
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>&
ndarray<T, N, Allocator>::
operator=(ndarray&& other)
{
    if (&other == this) return *this;

    constexpr bool should_copy_alloc = std::allocator_traits<Allocator>::
        propagate_on_container_move_assignment::value;
    const bool should_transfer_ownership =
        should_copy_alloc || _alloc == other._alloc;

    this->destroy();

    if (should_transfer_ownership) {
        if constexpr (should_copy_alloc) _alloc = other._alloc;
        _view = std::exchange(other._view, { { 0 }, nullptr });
    } else {
        // Just in case make_allocated_view throws
        _view = { { 0 }, nullptr };

        _view = this->make_allocated_view(other.shape());

        this->move_construct(other.begin(), other.end());
    }

    return *this;
}

template<typename T, std::size_t N, typename Allocator>
decltype(auto)
ndarray<T, N, Allocator>::
operator[](std::size_t idx) const noexcept
{
    return this->cview()[idx];
}

template<typename T, std::size_t N, typename Allocator>
decltype(auto)
ndarray<T, N, Allocator>::
operator[](std::size_t idx) noexcept
{
    return this->view()[idx];
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
operator ndarray_view<T, N>() noexcept
{
    return this->view();
}

template<typename T, std::size_t N, typename Allocator>
ndarray<T, N, Allocator>::
operator ndarray_view<const T, N>() const noexcept
{
    return this->cview();
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<T, N>
ndarray<T, N, Allocator>::
view() noexcept
{
    return _view;
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<const T, N>
ndarray<T, N, Allocator>::
view() const noexcept
{
    return _view;
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<const T, N>
ndarray<T, N, Allocator>::
cview() const noexcept
{
    return _view;
}

template<typename T, std::size_t N, typename Allocator>
std::size_t
ndarray<T, N, Allocator>::
element_count() const noexcept
{
    return _view.element_count();
}

template<typename T, std::size_t N, typename Allocator>
const std::array<std::size_t, N>&
ndarray<T, N, Allocator>::
shape() const noexcept
{
    return _view.shape();
}

template<typename T, std::size_t N, typename Allocator>
std::size_t
ndarray<T, N, Allocator>::
shape(std::size_t dim) const noexcept
{
    return _view.shape(dim);
}

template<typename T, std::size_t N, typename Allocator>
template<std::size_t M>
ndarray_view<T, M>
ndarray<T, N, Allocator>::
reshape(const std::array<std::size_t, M>& new_shape) noexcept
{
    return this->view().reshape(new_shape);
}

template<typename T, std::size_t N, typename Allocator>
template<std::size_t M>
ndarray_view<const T, M>
ndarray<T, N, Allocator>::
reshape(const std::array<std::size_t, M>& new_shape) const noexcept
{
    return this->cview().reshape(new_shape);
}

template<typename T, std::size_t N, typename Allocator>
template<std::size_t M>
ndarray_view<T, M>
ndarray<T, N, Allocator>::
reshape(const std::size_t (&new_shape)[M]) noexcept
{
    return this->view().reshape(new_shape);
}

template<typename T, std::size_t N, typename Allocator>
template<std::size_t M>
ndarray_view<const T, M>
ndarray<T, N, Allocator>::
reshape(const std::size_t (&new_shape)[M]) const noexcept
{
    return this->cview().reshape(new_shape);
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<T, 1>
ndarray<T, N, Allocator>::
flatten() noexcept
{
    return this->view().flatten();
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<const T, 1>
ndarray<T, N, Allocator>::
flatten() const noexcept
{
    return this->cview().flatten();
}

template<typename T, std::size_t N, typename Allocator>
T*
ndarray<T, N, Allocator>::
data() noexcept
{
    return _view.data();
}

template<typename T, std::size_t N, typename Allocator>
const T*
ndarray<T, N, Allocator>::
data() const noexcept
{
    return _view.data();
}

template<typename T, std::size_t N, typename Allocator>
Allocator
ndarray<T, N, Allocator>::
get_allocator() const noexcept
{
    return _alloc;
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<T, N>
ndarray<T, N, Allocator>::
slice(std::size_t offset) noexcept
{
    return this->view().slice(offset);
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<const T, N>
ndarray<T, N, Allocator>::
slice(std::size_t offset) const noexcept
{
    return this->cview().slice(offset);
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<T, N>
ndarray<T, N, Allocator>::
slice(std::size_t offset, std::size_t count) noexcept
{
    return this->view().slice(offset, count);
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<const T, N>
ndarray<T, N, Allocator>::
slice(std::size_t offset, std::size_t count) const noexcept
{
    return this->cview().slice(offset, count);
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::iterator
ndarray<T, N, Allocator>::
begin() noexcept
{
    return _view.begin();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_iterator
ndarray<T, N, Allocator>::
begin() const noexcept
{
    return _view.cbegin();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_iterator
ndarray<T, N, Allocator>::
cbegin() const noexcept
{
    return _view.cbegin();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::iterator
ndarray<T, N, Allocator>::
end() noexcept
{
    return _view.end();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_iterator
ndarray<T, N, Allocator>::
end() const noexcept
{
    return _view.cend();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_iterator
ndarray<T, N, Allocator>::
cend() const noexcept
{
    return _view.cend();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::reverse_iterator
ndarray<T, N, Allocator>::
rbegin() noexcept
{
    return _view.rbegin();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_reverse_iterator
ndarray<T, N, Allocator>::
rbegin() const noexcept
{
    return _view.crbegin();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_reverse_iterator
ndarray<T, N, Allocator>::
crbegin() const noexcept
{
    return _view.crbegin();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::reverse_iterator
ndarray<T, N, Allocator>::
rend() noexcept
{
    return _view.rend();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_reverse_iterator
ndarray<T, N, Allocator>::
rend() const noexcept
{
    return _view.crend();
}

template<typename T, std::size_t N, typename Allocator>
typename ndarray<T, N, Allocator>::const_reverse_iterator
ndarray<T, N, Allocator>::
crend() const noexcept
{
    return _view.crend();
}

template<typename T, std::size_t N, typename Allocator>
void
ndarray<T, N, Allocator>::
swap(ndarray<T, N, Allocator>& other) noexcept
{
    using std::swap;

    constexpr bool should_swap_alloc = std::allocator_traits<Allocator>::
        propagate_on_container_swap::value;

    if constexpr (should_swap_alloc) {
        swap(_alloc, other._alloc);
    } else {
        assert(_alloc == other._alloc);
    }

    swap(_view, other._view);
}

template<typename T, std::size_t N, typename Allocator>
ndarray_view<T, N>
ndarray<T, N, Allocator>::
make_allocated_view(const std::array<std::size_t, N>& shape_)
{
    T* data_ = std::allocator_traits<Allocator>::allocate(
        _alloc, detail::count_elements(shape_));
    return { shape_, data_ };
}

template<typename T, std::size_t N, typename Allocator>
template<typename InputIt>
void
ndarray<T, N, Allocator>::
copy_construct(InputIt first, InputIt last)
{
    static_assert(std::is_copy_constructible_v<T>);

    assert(std::distance(first, last) == std::ptrdiff_t(this->element_count()));

    if constexpr (std::is_nothrow_copy_constructible_v<T>) {
        for (auto dest = this->begin(); first != last; ++first, ++dest) {
            std::allocator_traits<Allocator>::construct(_alloc, dest, *first);
        }
    } else {
        auto dest = this->begin();
        try {
            for (; first != last; ++first, ++dest) {
                std::allocator_traits<Allocator>::construct(
                    _alloc, dest, *first);
            }
        } catch (...) {
            // If this occurs when called from the constructor, the destructor
            // won't run. If this occurs when called from the assignment
            // operator, the destructor has no way of knowing which elements
            // were successfully constructed. So in either case we need to clean
            // up.
            this->destroy(this->begin(), dest);
            _view = { { 0 }, nullptr };
            throw;
        }
    }
}

template<typename T, std::size_t N, typename Allocator>
void
ndarray<T, N, Allocator>::
move_construct(iterator first, iterator last)
{
    static_assert(std::is_move_constructible_v<T>);

    assert(std::distance(first, last) == std::ptrdiff_t(this->element_count()));

    if constexpr (std::is_nothrow_move_constructible_v<T>) {
        for (auto dest = this->begin(); first != last; ++first, ++dest) {
            std::allocator_traits<Allocator>::construct(
                _alloc, dest, std::move(*first));
        }
    } else {
        auto dest = this->begin();
        try {
            for (; first != last; ++first, ++dest) {
                std::allocator_traits<Allocator>::construct(
                    _alloc, dest, std::move(*first));
            }
        } catch (...) {
            // If this occurs when called from the constructor, the destructor
            // won't run. If this occurs when called from the assignment
            // operator, the destructor has no way of knowing which elements
            // were successfully constructed. So in either case we need to clean
            // up.
            this->destroy(this->begin(), dest);
            _view = { { 0 }, nullptr };
            throw;
        }
    }
}

template<typename T, std::size_t N, typename Allocator>
void
ndarray<T, N, Allocator>::
destroy() noexcept
{
    this->destroy(this->begin(), this->end());
}

template<typename T, std::size_t N, typename Allocator>
void
ndarray<T, N, Allocator>::
destroy(iterator first, iterator last) noexcept
{
    static_assert(std::is_nothrow_destructible_v<T>);

    while (first != last) {
        std::allocator_traits<Allocator>::destroy(_alloc, first++);
    }
    std::allocator_traits<Allocator>::deallocate(
        _alloc, this->data(), this->element_count());
}

template<typename T, std::size_t N, typename Allocator>
bool
operator==(const ndarray<T, N, Allocator>& a, const ndarray<T, N, Allocator>& b)
{
    if (a.shape() != b.shape()) return false;

    return std::equal(a.begin(), a.end(), b.begin());
}

template<typename T, std::size_t N, typename Allocator>
bool
operator!=(const ndarray<T, N, Allocator>& a, const ndarray<T, N, Allocator>& b)
{
    return !(a == b);
}

template<typename T, std::size_t N, typename Allocator>
std::ostream&
operator<<(std::ostream& os, const ndarray<T, N, Allocator>& a)
{
    return os << a.view();
}

template<typename T, std::size_t N, typename Allocator>
void
swap(ndarray<T, N, Allocator>& a, ndarray<T, N, Allocator>& b) noexcept
{
    a.swap(b);
}

} // namespace vt

#endif // VT_NDARRAY_IMPL_CONTAINER_IPP_
