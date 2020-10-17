deduction guides for vt::ndarray_view
=====================================

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N>
ndarray_view(const std::size_t (&)[N], T*) -> ndarray_view<T, N>;
```

This deduction guide is provided for `ndarray_view` to allow deduction from an array literal as `shape` argument.

Example
-------

```c++
#include <vt/ndarray/view.hpp>

int main()
{
    const int data[4] = { 0 };

    // Uses explicit deduction guide to deduce vt::ndarray_view<const int, 2>
    vt::ndarray_view view{{ 2, 2 }, data};
}
```
