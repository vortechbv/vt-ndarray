vt::ndview::ndview
==================

```c++
constexpr
ndview(const std::array<std::size_t, N>& shape, T* data) noexcept;
```

Constructs the view for the given shape over the given data.

The behavior is undefined if the array pointed to by `data` contains less than `shape[0] * ... * shape[N-1]` elements.

Parameters
----------

|||
--------- | --------------------------------------------------------------------
**shape** | an array containing the size of the data in each dimension
**data**  | a pointer to the array containing the data that is to be viewed into
