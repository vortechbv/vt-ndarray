vt::ndarray::operator ndview, vt::ndarray::view
===============================================

```c++
// (1)
operator ndview<T, N>() noexcept;
// (1)
operator ndview<const T, N>() const noexcept;
// (2)
ndview<T, N>
view() noexcept;
// (2)
ndview<const T, N>
view() const noexcept;
// (3)
ndview<const T, N>
cview() const noexcept;
```

Creates a view into the container.

1. Implicit conversion. Constness of the view depends on the constness of `*this`.
2. Explicit conversion. Constness of the view depends on the constness of `*this`.
3. Explicit conversion to const view.

Return value
------------

A view into the container.
