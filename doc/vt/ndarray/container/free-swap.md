vt::swap(vt::ndarray)
=====================

- Defined in header `<vt/ndarray/container.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N, typename Allocator>
void
swap(ndarray<T, N, Allocator>& a, ndarray<T, N, Allocator>& b) noexcept;
```

Swaps the contents of `a` and `b`. Calls `a.swap(b)`.

Parameters
----------

|||
-------- | ---------------------------------
**a, b** | containers whose contents to swap
