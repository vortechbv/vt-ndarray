vt::ndarray::operator ndarray_view, vt::ndarray::view
=====================================================

```c++
// (1)
operator ndarray_view<T, N>() noexcept;
// (1)
operator ndarray_view<const T, N>() const noexcept;
// (2)
ndarray_view<T, N>
view() noexcept;
// (2)
ndarray_view<const T, N>
view() const noexcept;
// (3)
ndarray_view<const T, N>
cview() const noexcept;
```

Creates a view into the container.

1. Implicit conversion. Constness of the view depends on the constness of `*this`.
2. Explicit conversion. Constness of the view depends on the constness of `*this`.
3. Explicit conversion to const view.

Return value
------------

A view into the container.
