vt::r
=====

```c++
// (1)
constexpr index_range<0> r() noexcept;
// (2)
constexpr index_range<1> r(std::size_t start) noexcept;
// (3)
constexpr index_range<2> r(std::size_t start, std::size_t end) noexcept;
```

Convenience function for creating instances of `vt::index_range`.

1. Creates an index range from the start of an array dimension to the end of an array dimension. (Similar to `:` in Python.)
2. Creates an index range from a specified start to the end of an array dimension. (Similar to `start:` in Python.)
3. Creates an index range from a specified start to a specified end. (Similar to `start:end` in Python.)

The behavior is undefined if `start` or `end` are outside the bounds of the array that the resulting `vt::index_range` indexes into.

Parameters
----------

|||
--------- | -----------------------------------
**start** | start index of the range
**end**   | one past the end index of the range

Return value
------------

The resulting `vt::index_range`.
