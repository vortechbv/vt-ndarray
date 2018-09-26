vt::ndarray::rend, vt::ndarray::crend
=====================================

```c++
reverse_iterator
rend() noexcept;
const_reverse_iterator
rend() const noexcept;
const_reverse_iterator
crend() const noexcept;
```

Returns a reverse iterator to the element following the last element of the reversed array. It corresponds to the element preceding the first element of the non-reversed array. This element acts as a placeholder, attempting to access it results in undefined behavior.

- `rend()` returns a mutable or constant iterator, depending on the constness of `*this`.
- `crend()` always returns a constant iterator.

Return value
------------

A reverse iterator to the element following the last element.
