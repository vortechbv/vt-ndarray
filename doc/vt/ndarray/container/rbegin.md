vt::ndarray::rbegin, vt::ndarray::crbegin
=========================================

```c++
reverse_iterator rbegin() noexcept;
const_reverse_iterator rbegin() const noexcept;
const_reverse_iterator crbegin() const noexcept;
```

Returns a reverse iterator to the first element of the reversed array. It corresponds to the last element of the non-reversed array.

- `rbegin()` returns a mutable or constant iterator, depending on the constness of `*this`.
- `crbegin()` always returns a constant iterator.

Return value
------------

A reverse iterator to the first element.
