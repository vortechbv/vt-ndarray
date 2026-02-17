vt::ndarray::flatten
====================

```c++
// (1)
ndview<T, 1> flatten() noexcept;
// (2)
ndview<const T, 1> flatten() const noexcept;
```

Creates a view into this array with a flattened shape. That is, the newly created view will be 1-dimensional and contains all elements of this array.

1. Obtains a mutable view with flattened shape.
2. Obtains a const view with flattened shape.

Return value
------------

A view with a flattened shape.

Example
-------

```c++
#include <vt/ndarray/container.hpp>
#include <cassert>

int main() {
    const vt::ndarray<int, 3> A{{ 2, 2, 2 }, {
        3, 1,
        4, 1,

        5, 9,
        2, 6
    }};

    const vt::ndview<const int, 1> b = A.flatten();
    assert(b.shape(0) == 8);
    assert(b[0] == 3);
    assert(b[1] == 1);
    assert(b[2] == 4);
    assert(b[3] == 1);
    assert(b[4] == 5);
    assert(b[5] == 9);
    assert(b[6] == 2);
    assert(b[7] == 6);
}
```
