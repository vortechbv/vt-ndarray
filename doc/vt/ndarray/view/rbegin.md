vt::ndview::rbegin, vt::ndview::crbegin
=======================================

```c++
// (1)
constexpr reverse_iterator rbegin() const noexcept;
// (2)
constexpr const_reverse_iterator crbegin() const noexcept;
```

Returns a reverse iterator to the first element of the reversed view. It corresponds to the last element of the non-reversed view.

1. Returns a mutable or constant iterator, depending on the constness of `T`.
2. Always returns a constant iterator.

Return value
------------

A reverse iterator to the first element.
