vt::ndarray::begin, vt::ndarray::cbegin
=======================================

```c++
iterator
begin() noexcept;
const_iterator
begin() const noexcept;
const_iterator
cbegin() const noexcept;
```

Returns an iterator to the first element of the array.

- `begin()` returns a mutable or constant iterator, depending on the constness of `*this`.
- `cbegin()` always returns a constant iterator.

Return value
------------

An iterator to the first element.
