vt::ndslice::ndslice
====================

```c++
// (1)
constexpr ndslice(
    const std::array<std::size_t, N>& shape,
    T* data
) noexcept;
// (2)
constexpr ndslice(
    const std::array<std::size_t, N>& shape,
    const std::array<std::size_t, N>& strides,
    T* data
) noexcept;
// (3)
constexpr ndslice(
    const vt::ndview<T, N>& view
) noexcept;
// (4)
constexpr ndslice(
    const vt::ndview<std::remove_const_t<T>, N>& view
) noexcept requires(std::is_const_v<T>);
// (5)
template<ndview_compatible_range<T> R>
constexpr ndslice(R&& r) noexcept requires(N == 1);
// (6)
constexpr ndslice(
    std::initializer_list<std::remove_cv_t<T>> il
) noexcept requires(std::is_const_v<T> && N == 1);
```

Constructs the slice for the given shape and strides over the given data, or for the given view, range or initializer list.

1. Constructs the slice with strides that assume contiguous, row-major data.
2. Constructs the slice with specified strides.
3. Constructs the slice from a contiguous view.
4. Same as (3), but for the case where the slice data is const and the view data is not.
5. Constructs the 1D slice from the given contiguous range.
6. Constructs the 1D slice from the given initializer list.

Parameters
----------

|||
----------- | ----------------------------------------------
**shape**   | an array containing the size of each dimension
**strides** | an array containing the strides of the slice
**data**    | a pointer to the array
**view**    | view to base the slice on
**r**       | a contiguous range to base the slice on
**il**      | an initializer list to base the slice on
