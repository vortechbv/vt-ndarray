vt::ndarray::end, vt::ndarray::cend
===================================

```c++
iterator end() noexcept;
const_iterator end() const noexcept;
const_iterator cend() const noexcept;
```

Returns an iterator to the element following the last element in the array. This element acts as a placeholder, attempting to access it results in undefined behavior.

- `end()` returns a mutable or constant iterator, depending on the constness of `*this`.
- `cend()` always returns a constant iterator.

Return value
------------

An iterator to the element following the last element.
