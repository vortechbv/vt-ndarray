vt::ndslice::operator ndslice
=============================

```c++
constexpr operator ndslice<const T, N>() const noexcept;
```

Implicit conversion to a slice into constant data. Comparable to the implicit conversion of `T*` to `const T*`.

Return value
------------

This slice, but with const data.
