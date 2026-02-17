vt::ndarray::slice
==================

```c++
// (1)
ndview<T, N> slice(std::size_t offset) noexcept;
// (2)
ndview<const T, N> slice(std::size_t offset) const noexcept;
// (3)
ndview<T, N> slice(std::size_t offset, std::size_t count) noexcept;
// (4)
ndview<const T, N> slice(std::size_t offset, std::size_t count) const noexcept;
```

Creates a slice in the first dimension of the array. The shape of the remaining dimensions will remain the same.

1. Obtains a mutable view of the slice `[offset, shape[0])`.
2. Obtains a const view of the slice `[offset, shape[0])`.
3. Obtains a mutable view of the slice `[offset, offset + count)`.
4. Obtains a const view of the slice `[offset, offset + count)`.

The behavior is undefined if `offset > shape[0]` or if `offset + count > shape[0]`.

Parameters
----------

|||
---------- | -------------------------------------
**offset** | position of the first view or element
**count**  | requested length

Return value
------------

A view that is a slice of the original array.

Example
-------

```c++
#include <vt/ndarray/container.hpp>
#include <cassert>

int main() {
    const vt::ndarray<int, 2> A{{ 4, 2 }, {
        3, 1,
        4, 1,
        5, 9,
        2, 6
    }};

    // When slicing a 2D-array, rows outside of the slice will not be in the
    // obtained view
    vt::ndview<const int, 2> B = A.slice(1, 2);
    assert(B[0][0] == 4);
    assert(B[0][1] == 1);
    assert(B[1][0] == 5);
    assert(B[1][1] == 9);
}
```
