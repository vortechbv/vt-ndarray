vt::ndview::end, vt::ndview::cend
=================================

```c++
// (1)
constexpr iterator end() const noexcept;
// (2)
constexpr const_iterator cend() const noexcept;
```

Returns an iterator to the element following the last element in the view. This element acts as a placeholder, attempting to access it results in undefined behavior.

1. Returns a mutable or constant iterator, depending on the constness of `T`.
2. Always returns a constant iterator.

Return value
------------

An iterator to the element following the last element.
