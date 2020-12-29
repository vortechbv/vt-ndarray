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

#ifndef VT_NDARRAY_CONTAINER_HPP_
#define VT_NDARRAY_CONTAINER_HPP_

#include <vt/ndarray/allocator.hpp>
#include <vt/ndarray/view.hpp>

#include <array>
#include <initializer_list>
#include <memory>
#include <type_traits>

#if __has_include(<memory_resource>)
#   include <memory_resource>
#endif

namespace vt {

template<typename T, std::size_t N, typename Allocator = ndarray_allocator<T>>
class ndarray {
    static_assert(std::is_same_v<std::remove_cv_t<T>, T>);
    static_assert(std::is_same_v<T, typename Allocator::value_type>);

public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = typename ndarray_view<T, N>::iterator;
    using const_iterator = typename ndarray_view<T, N>::const_iterator;
    using reverse_iterator = typename ndarray_view<T, N>::reverse_iterator;
    using const_reverse_iterator =
        typename ndarray_view<T, N>::const_reverse_iterator;

    static constexpr std::size_t dim_count = N;

    ndarray() noexcept(noexcept(Allocator{}));
    explicit
    ndarray(const Allocator& alloc) noexcept;
    explicit
    ndarray(
        const std::array<std::size_t, N>& shape_,
        const Allocator& alloc = Allocator{});
    ndarray(
        const std::array<std::size_t, N>& shape_, const T& init,
        const Allocator& alloc = Allocator{});
    template<typename InputIt>
    ndarray(
        const std::array<std::size_t, N>& shape_,
        InputIt first, InputIt last,
        const Allocator& alloc = Allocator{});
    ndarray(
        const std::array<std::size_t, N>& shape_,
        std::initializer_list<T> init,
        const Allocator& alloc = Allocator{});
    ndarray(const ndarray& other);
    ndarray(const ndarray& other, const Allocator& alloc);
    ndarray(ndarray&& other) noexcept;
    ndarray(ndarray&& other, const Allocator& alloc);

    ~ndarray();

    ndarray&
    operator=(const ndarray& other);
    ndarray&
    operator=(ndarray&& other);

    decltype(auto)
    operator[](std::size_t idx) noexcept;
    decltype(auto)
    operator[](std::size_t idx) const noexcept;

    operator ndarray_view<T, N>() noexcept;
    operator ndarray_view<const T, N>() const noexcept;

    ndarray_view<T, N>
    view() noexcept;
    ndarray_view<const T, N>
    view() const noexcept;
    ndarray_view<const T, N>
    cview() const noexcept;

    std::size_t
    element_count() const noexcept;

    const std::array<std::size_t, N>&
    shape() const noexcept;
    std::size_t
    shape(std::size_t dim) const noexcept;

    template<std::size_t M>
    ndarray_view<T, M>
    reshape(const std::array<std::size_t, M>& new_shape) noexcept;
    template<std::size_t M>
    ndarray_view<const T, M>
    reshape(const std::array<std::size_t, M>& new_shape) const noexcept;
    template<std::size_t M>
    ndarray_view<T, M>
    reshape(const std::size_t (&new_shape)[M]) noexcept;
    template<std::size_t M>
    ndarray_view<const T, M>
    reshape(const std::size_t (&new_shape)[M]) const noexcept;

    T*
    data() noexcept;
    const T*
    data() const noexcept;

    Allocator
    get_allocator() const noexcept;

    constexpr vt::ndarray_view<T, N>
    slice(std::size_t offset) noexcept;
    constexpr vt::ndarray_view<const T, N>
    slice(std::size_t offset) const noexcept;
    constexpr vt::ndarray_view<T, N>
    slice(std::size_t offset, std::size_t count) noexcept;
    constexpr vt::ndarray_view<const T, N>
    slice(std::size_t offset, std::size_t count) const noexcept;

    iterator
    begin() noexcept;
    const_iterator
    begin() const noexcept;
    const_iterator
    cbegin() const noexcept;

    iterator
    end() noexcept;
    const_iterator
    end() const noexcept;
    const_iterator
    cend() const noexcept;

    reverse_iterator
    rbegin() noexcept;
    const_reverse_iterator
    rbegin() const noexcept;
    const_reverse_iterator
    crbegin() const noexcept;

    reverse_iterator
    rend() noexcept;
    const_reverse_iterator
    rend() const noexcept;
    const_reverse_iterator
    crend() const noexcept;

    void
    swap(ndarray& other) noexcept;

private:
    Allocator _alloc;
    ndarray_view<T, N> _view;

    [[nodiscard]] ndarray_view<T, N>
    make_allocated_view(const std::array<std::size_t, N>& shape_);

    template<typename InputIt>
    void
    copy_construct(InputIt first, InputIt last);
    void
    move_construct(iterator first, iterator last);

    void
    destroy() noexcept;
    void
    destroy(iterator first, iterator last) noexcept;
};

#if __has_include(<memory_resource>)

namespace pmr {

template<typename T, std::size_t N>
using ndarray = vt::ndarray<T, N, std::pmr::polymorphic_allocator<T>>;

} // namespace pmr

#endif // __has_include(<memory_resource>)

template<typename T, std::size_t N, typename Allocator>
bool
operator==(
    const ndarray<T, N, Allocator>& a, const ndarray<T, N, Allocator>& b);
template<typename T, std::size_t N, typename Allocator>
bool
operator!=(
    const ndarray<T, N, Allocator>& a, const ndarray<T, N, Allocator>& b);

template<typename T, std::size_t N, typename Allocator>
std::ostream&
operator<<(std::ostream& os, const ndarray<T, N, Allocator>& a);

template<typename T, std::size_t N, typename Allocator>
void
swap(ndarray<T, N, Allocator>& a, ndarray<T, N, Allocator>& b) noexcept;

} // namespace vt

#include <vt/ndarray/impl/container.ipp>

#endif // VT_NDARRAY_CONTAINER_HPP_
