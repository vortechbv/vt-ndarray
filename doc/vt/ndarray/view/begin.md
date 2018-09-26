vt::ndarray_view::begin, vt::ndarray_view::cbegin
=================================================

```c++
// (1)
constexpr iterator
begin() const noexcept;
// (2)
constexpr const_iterator
cbegin() const noexcept;
```

Returns an iterator to the first element in the view.

1. Returns a mutable or constant iterator, depending on the constness of `T`.
2. Always returns a constant iterator.

Return value
------------

An iterator to the first element.
