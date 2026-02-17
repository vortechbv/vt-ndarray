vt::ndarray::shape
==================

```c++
// (1)
const std::array<std::size_t, N>& shape() const noexcept;
// (2)
std::size_t shape(std::size_t dim) const noexcept;
```

Returns the shape of this array.

1. Returns the N-dimensional shape of this array.
2. Returns the size of dimension `dim`, as if by calling `.shape()[dim];`. The behavior is undefined if `dim >= N`.

Parameters
----------

|||
------- | ----------------------------------------
**dim** | dimension for which to retrieve the size

Return value
------------

The shape of this array.
