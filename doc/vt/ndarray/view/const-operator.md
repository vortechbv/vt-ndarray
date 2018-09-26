vt::ndarray_view::operator ndarray_view
=======================================

```c++
constexpr
operator ndarray_view<const T, N>() const noexcept;
```

Implicit conversion to a view into constant data. Comparable to the implicit conversion of `T*` to `const T*`.

Return value
------------

This view, but with const data.
