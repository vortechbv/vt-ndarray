vt::ndview::operator[]
======================

```c++
decltype(auto) operator[](std::size_t idx) const noexcept;
```

Accesses the view or element at the specified index. The behavior is undefined if `idx >= shape[0]`.

Parameters
----------

|||
------- | --------------------------------------
**idx** | index of the view or element to access

Return value
------------

If `N > 1`, returns a view of dimension `N - 1` into the sub-array at the specified index.

If `N = 1`, returns a reference to the element at the specified index.

Example
-------

```c++
#include <vt/ndarray/view.hpp>
#include <cassert>

int main()
{
    const int A_data[] = {
        3, 1, 4,
        1, 5, 9
    };
    vt::ndview<const int, 2> A{{ 2, 3 }, A_data};

    // Elements can be accessed by chaining calls to operator[]
    assert(A[1][1] == 5);

    // A single call to operator[] will return a view into a sub-array
    vt::ndview<const int, 1> A_0 = A[0];
    assert(A_0[0] == 3);
    assert(A_0[1] == 1);
    assert(A_0[2] == 4);
}
```
