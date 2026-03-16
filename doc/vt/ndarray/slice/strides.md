vt::ndslice::strides
====================

```c++
// (1)
constexpr const std::array<std::size_t, N>& strides() const noexcept;
// (2)
constexpr std::size_t strides(std::size_t dim) const noexcept;
```

Returns the strides of this slice.

1. Returns the N-dimensional strides of this slice.
2. Returns the size of dimension `dim`, as if by calling `.strides()[dim];`. The behavior is undefined if `dim >= N`.

Parameters
----------

|||
------- | ----------------------------------------
**dim** | dimension for which to retrieve the size

Return value
------------

The strides of this slice.
