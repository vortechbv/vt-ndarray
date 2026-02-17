vt::ndview::operator ndview
===========================

```c++
constexpr operator ndview<const T, N>() const noexcept;
```

Implicit conversion to a view into constant data. Comparable to the implicit conversion of `T*` to `const T*`.

Return value
------------

This view, but with const data.
