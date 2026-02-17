vt::ndview::rend, vt::ndview::crend
===================================

```c++
// (1)
constexpr reverse_iterator rend() const noexcept;
// (2)
constexpr const_reverse_iterator crend() const noexcept;
```

Returns a reverse iterator to the element following the last element of the reversed view. It corresponds to the element preceding the first element of the non-reversed view. This element acts as a placeholder, attempting to access it results in undefined behavior.

1. Returns a mutable or constant iterator, depending on the constness of `T`.
2. Always returns a constant iterator.

Return value
------------

A reverse iterator to the element following the last element.
