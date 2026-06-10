vt::index_range
===============

- Defined in header `<vt/ndarray/index.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<std::size_t N>
struct index_range;
```

Represents a range of indices, for creating a slice when indexing into an array. Either from the start of an array dimension to the end of an array dimension (`index_range<0>`), from a specified start to the end of an array dimension (`index_range<1>`), or from a specified start to a specified end (`index_range<2>`).

Non-member functions
--------------------

|||
------------- | --------------------------------------------------
[r](r.md#top) | convenience function for creating an `index_range`

Example
-------

```c++
#include <vt/ndarray/container.hpp>
#include <iostream>

int main() {
    // Use the vt::r convenience function to reduce clutter when creating
    // instances of vt::index_range when performing a slicing operation.
    using vt::r;

    const vt::ndarray<int, 3> a{{ 2, 3, 4 }, {
        3, 1, 4, 1,
        5, 9, 2, 6,
        5, 3, 5, 8,

        9, 7, 9, 3,
        2, 3, 8, 4,
        6, 2, 6, 4
    }};

    std::cout << a[1, r(1), r(1, 3)] << '\n';
}
```

Output:

```
[[3,8],[2,6]]
```
