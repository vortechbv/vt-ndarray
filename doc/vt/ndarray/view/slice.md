vt::ndarray_view::slice
=======================

```c++
// (1)
constexpr vt::ndarray_view<T, N>
slice(std::size_t offset) const noexcept;
// (2)
constexpr vt::ndarray_view<T, N>
slice(std::size_t offset, std::size_t count) const noexcept;
```

Creates a slice in the first dimension of the view. The shape of the remaining dimensions will remain the same.

1. Obtains a view of the slice `[offset, shape[0])`.
2. Obtains a view of the slice `[offset, offset + count)`.

The behavior is undefined if `offset > shape[0]` or if `offset + count > shape[0]`.

Parameters
----------

|||
---------- | -------------------------------------
**offset** | position of the first view or element
**count**  | requested length

Return value
------------

A view that is a slice of the original view.

Example
-------

```c++
#include <vt/ndarray/view.hpp>
#include <cassert>

int main()
{
    const int A_data[] = {
        3, 1,
        4, 1,
        5, 9,
        2, 6
    };
    vt::ndarray_view<const int, 2> A{{ 4, 2 }, A_data};

    // When slicing a 2D-array, rows outside of the slice will not be in the
    // obtained view
    vt::ndarray_view<const int, 2> B = A.slice(1, 2);
    assert(B[0][0] == 4);
    assert(B[0][1] == 1);
    assert(B[1][0] == 5);
    assert(B[1][1] == 9);
}
```
