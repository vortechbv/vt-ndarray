vt::ndview::reshape
===================

```c++
// (1)
template<std::size_t M>
constexpr ndview<T, M> reshape(
    const std::array<std::size_t, M>& new_shape
) const noexcept;
// (2)
template<std::size_t M>
constexpr ndview<T, M> reshape(
    const std::size_t (&new_shape)[M]
) const noexcept;
```

Creates a new view into the same array, but with a different shape. The number of dimensions in the new shape may differ from the original shape.

1. Obtains a view with shape `new_shape`.
2. Provided only for automatic template argument deduction. Behavior is the same as 1.

The behavior is undefined if the total number of elements in the new shape does not match the total number of elements in the original shape.

Parameters
----------

|||
------------- | ---------------------
**new_shape** | shape of the new view

Return value
------------

A view with a different shape than the shape of the original view.

Example
-------

```c++
#include <vt/ndarray/view.hpp>
#include <cassert>

int main()
{
    const int A_data[] = { 3, 1, 4, 1 };
    vt::ndview<const int, 2> A{{ 4 }, A_data};
    assert(A[0] == 3);
    assert(A[1] == 1);
    assert(A[2] == 4);
    assert(A[3] == 1);

    vt::ndview<const int, 2> B = A.reshape({ 2, 2 });
    assert(B[0][0] == 3);
    assert(B[0][1] == 1);
    assert(B[1][0] == 4);
    assert(B[1][1] == 1);
}
```
