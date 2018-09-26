// Copyright (c) 2018 VORtech b.v.
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

#ifndef VT_NDARRAY_ALLOCATOR_HPP_
#define VT_NDARRAY_ALLOCATOR_HPP_

#include <memory>
#include <type_traits>

namespace vt {

template<typename T>
class ndarray_allocator {
    static_assert(std::is_same_v<std::remove_cv_t<T>, T>);

public:
    using value_type = T;

    constexpr
    ndarray_allocator() noexcept;
    explicit constexpr
    ndarray_allocator(std::align_val_t align_val_) noexcept;
    template<typename U>
    constexpr
    ndarray_allocator(const ndarray_allocator<U>& other) noexcept;

    [[nodiscard]] T*
    allocate(std::size_t n) const;

    void
    deallocate(T* p, std::size_t n) const noexcept;

    template<typename U>
    void
    construct(U* p) const noexcept(std::is_nothrow_default_constructible_v<U>);

    template<typename U>
    void
    destroy(U* p) const noexcept(std::is_nothrow_destructible_v<U>);

    constexpr std::size_t
    align_val() const noexcept;

private:
    std::align_val_t _align_val;
};

template<typename T1, typename T2>
constexpr bool
operator==(const ndarray_allocator<T1>& lhs, const ndarray_allocator<T2>& rhs)
noexcept;
template<typename T1, typename T2>
constexpr bool
operator!=(const ndarray_allocator<T1>& lhs, const ndarray_allocator<T2>& rhs)
noexcept;

} // namespace vt

#include <vt/ndarray/impl/allocator.ipp>

#endif // VT_NDARRAY_ALLOCATOR_HPP_
