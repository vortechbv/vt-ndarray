deduction guides for vt::ndslice
================================

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N>
ndslice(const std::size_t (&)[N], T*) -> ndslice<T, N>;

template<typename T, std::size_t N>
ndslice(
    const std::size_t (&)[N],
    const std::size_t (&)[N],
    T*
) -> ndslice<T, N>;
```

This deduction guide is provided for `ndslice` to allow deduction from an array literal as `shape` or `strides` argument.

Example
-------

```c++
#include <vt/ndarray/view.hpp>

int main() {
    const int data[4] = { 0 };

    // Uses explicit deduction guide to deduce vt::ndslice<const int, 2>
    vt::ndslice view{{ 2, 2 }, { 2, 1}, data};
}
```
