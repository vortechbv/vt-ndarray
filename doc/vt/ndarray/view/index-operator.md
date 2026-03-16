vt::ndview::operator[]
======================

```c++
template<indexer... Index>
decltype(auto) operator[](
    Index... idx
) const noexcept requires((sizeof...(Index) <= N));
```

Accesses the view, slice or element at the specified indices or index ranges. The behavior is undefined if any indices are outside the bounds of the view.

If `sizeof...(Index) < N`, the result is similar to the arguments being padded with occurrences of [r()](../index-range/r.md#top) until `N` arguments are reached.

Parameters
----------

|||
------- | -----------------------------------------
**idx** | parameter-pack of indices or index ranges

Return value
------------

If all arguments in the parameter-pack are convertible to `std::size_t`, returns a reference to the element at the specified indices.

Else, if the parameter-pack specifies a contiguous slice, returns a [ndview](../view/readme.md#top) of the slice.

Else, if the parameter-pack specifies a non-contiguous slice, returns a [ndslice](../slice/readme.md#top).

Example
-------

```c++
#include <vt/ndarray/view.hpp>
#include <cassert>

int main() {
    using vt::r;

    const int A_data[] = {
        3, 1, 4,
        1, 5, 9
    };
    vt::ndview<const int, 2> A{{ 2, 3 }, A_data};

    // Elements can be accessed by specifying only indices
    assert(A[1, 1] == 5);

    // A contiguous slice will result in a vt::ndview
    vt::ndview<const int, 1> A_0j = A[0, r()];
    assert(A_0j[0] == 3);
    assert(A_0j[1] == 1);
    assert(A_0j[2] == 4);

    // A non-contiguous slice will result in a vt::ndslice
    vt::ndslice<const int, 1> A_i2 = A[r(), 2];
    assert(A_i2[0] == 4);
    assert(A_i2[1] == 9);
}
```
