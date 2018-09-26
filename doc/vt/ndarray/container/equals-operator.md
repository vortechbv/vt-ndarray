operator==,!=(vt::ndarray)
==========================

- Defined in header `<vt/ndarray/container.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
// (1)
template<typename T, std::size_t N, typename Allocator>
bool
operator==(
    const ndarray<T, N, Allocator>& a, const ndarray<T, N, Allocator>& b);
// (2)
template<typename T, std::size_t N, typename Allocator>
bool
operator!=(
    const ndarray<T, N, Allocator>& a, const ndarray<T, N, Allocator>& b);
```

Compares the shape and contents of two containers.

Parameters
----------

|||
---------| ----------------------------------------------
**a, b** | containers whose shape and contents to compare

Return value
------------

1. `true` if the shape and contents of the containers are equal, `false` otherwise.
2. `true` if the shape or contents of the containers are not equal, `false` otherwise.
