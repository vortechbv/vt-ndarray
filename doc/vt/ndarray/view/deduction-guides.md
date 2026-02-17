deduction guides for vt::ndview
===============================

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N>
ndview(const std::size_t (&)[N], T*) -> ndview<T, N>;
```

This deduction guide is provided for `ndview` to allow deduction from an array literal as `shape` argument.

Example
-------

```c++
#include <vt/ndarray/view.hpp>

int main() {
    const int data[4] = { 0 };

    // Uses explicit deduction guide to deduce vt::ndview<const int, 2>
    vt::ndview view{{ 2, 2 }, data};
}
```
