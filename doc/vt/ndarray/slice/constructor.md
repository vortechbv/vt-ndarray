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
```

Constructs the slice for the given shape and strides over the given data, or for the given view.

1. Constructs the slice with strides that assume contiguous, row-major data.
2. Constructs the slice with specified strides.
3. Constructs the slice from a contiguous view.
4. Same as (3), but for the case where the slice data is const and the view data is not.

Parameters
----------

|||
----------- | ----------------------------------------------
**shape**   | an array containing the size of each dimension
**strides** | an array containing the strides of the slice
**data**    | a pointer to the array
**view**    | view to base the slice on
