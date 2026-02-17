// Copyright (c) 2018-2026 VORtech b.v.
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

#ifndef VT_NDARRAY_IMPL_ALLOCATOR_IPP_
#define VT_NDARRAY_IMPL_ALLOCATOR_IPP_

#include <algorithm>
#include <cassert>


namespace vt {

namespace detail {

// This is not necessarily the cache-line size for every machine, but it is for
// most machines that we target. Users can optionally specify a different value
// by defining this macro.
#ifndef VT_CACHE_LINE_SIZE
#   define VT_CACHE_LINE_SIZE 64
#endif

inline constexpr std::size_t cache_line_size = VT_CACHE_LINE_SIZE;

} // namespace detail


template<typename T>
constexpr ndarray_allocator<T>::ndarray_allocator(
) noexcept :
    ndarray_allocator{
        std::align_val_t{std::max(detail::cache_line_size, alignof(T))}
    }
{
}


template<typename T>
constexpr ndarray_allocator<T>::ndarray_allocator(
    std::align_val_t align_val_
) noexcept : _align_val(align_val_) {
    assert(this->align_val() >= alignof(T));
}


template<typename T>
template<typename U>
constexpr ndarray_allocator<T>::ndarray_allocator(
    const ndarray_allocator<U>& other
) noexcept : _align_val{std::align_val_t{other.align_val()}} {
}


template<typename T>
T* ndarray_allocator<T>::allocate(std::size_t n) const {
    return static_cast<T*>(::operator new(n * sizeof(T), _align_val));
}


template<typename T>
void ndarray_allocator<T>::deallocate(
    T* p,
    std::size_t /* n */
) const noexcept {
    ::operator delete(p, _align_val);
}


template<typename T>
template<typename U>
void ndarray_allocator<T>::construct(
    U* p
) const noexcept(std::is_nothrow_default_constructible_v<U>) {
    if constexpr (std::is_fundamental_v<U>) {
        (void)p;
    } else {
        ::new (static_cast<void*>(p)) U();
    }
}


template<typename T>
template<typename U>
void ndarray_allocator<T>::destroy(
    U* p
) const noexcept(std::is_nothrow_destructible_v<U>) {
    // Specified manually, since if we let std::allocator_traits specify this
    // function, clang with libstdc++ will generate a loop with subroutine calls
    // for no-op destructors.
    p->~U();
}


template<typename T>
constexpr std::size_t ndarray_allocator<T>::align_val() const noexcept {
    return static_cast<std::size_t>(_align_val);
}


template<typename T1, typename T2>
constexpr bool operator==(
    const ndarray_allocator<T1>& lhs,
    const ndarray_allocator<T2>& rhs
) noexcept {
    // Since the alignment of an allocation must also be specified when
    // de-allocating, allocators are only interchangeable if their alignment
    // values are equal.
    return lhs.align_val() == rhs.align_val();
}


template<typename T1, typename T2>
constexpr bool operator!=(
    const ndarray_allocator<T1>& lhs,
    const ndarray_allocator<T2>& rhs
) noexcept {
    return !(lhs == rhs);
}

} // namespace vt

#endif // VT_NDARRAY_IMPL_ALLOCATOR_IPP_
