vt::ndarray::reshape
====================

```c++
// (1)
template<std::size_t M>
ndarray_view<T, M>
reshape(const std::array<std::size_t, M>& new_shape) noexcept;
// (2)
template<std::size_t M>
ndarray_view<const T, M>
reshape(const std::array<std::size_t, M>& new_shape) const noexcept;
// (3)
template<std::size_t M>
ndarray_view<T, M>
reshape(const std::size_t (&new_shape)[M]) noexcept;
// (4)
template<std::size_t M>
ndarray_view<const T, M>
reshape(const std::size_t (&new_shape)[M]) const noexcept;
```

Creates a view into this array with a different shape. The number of dimensions in the new shape may differ from the original shape.

1. Obtains a mutable view with shape `new_shape`.
2. Obtains a const view with shape `new_shape`.
3. Provided only for automatic template argument deduction. Behavior is the same as 1.
4. Provided only for automatic template argument deduction. Behavior is the same as 2.

The behavior is undefined if the total number of elements in the new shape does not match the total number of elements in the original shape.

Parameters
----------

|||
------------- | -----------------
**new_shape** | shape of the view

Return value
------------

A view with a different shape than the shape of this array.

Example
-------

```c++
#include <vt/ndarray/container.hpp>
#include <cassert>

int main()
{
    const vt::ndarray<int, 2> A{{ 4 }, { 3, 1, 4, 1 }};
    assert(A[0] == 3);
    assert(A[1] == 1);
    assert(A[2] == 4);
    assert(A[3] == 1);

    vt::ndarray_view<const int, 2> B = A.reshape({ 2, 2 });
    assert(B[0][0] == 3);
    assert(B[0][1] == 1);
    assert(B[1][0] == 4);
    assert(B[1][1] == 1);
}
```
