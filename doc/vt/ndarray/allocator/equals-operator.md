operator==,!=(vt::ndarray_allocator)
====================================

- Defined in header `<vt/ndarray/algorithm.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
// (1)
template<typename T1, typename T2>
constexpr bool
operator==(const ndarray_allocator<T1>& lhs, const ndarray_allocator<T2>& rhs)
noexcept;
// (2)
template<typename T1, typename T2>
constexpr bool
operator!=(const ndarray_allocator<T1>& lhs, const ndarray_allocator<T2>& rhs)
noexcept;
```

Compares two allocators. Allocators are interchangeable if their alignment value matches.

Parameters
----------

|||
------------ | ---------------------
**lhs, rhs** | allocators to compare

Return value
------------

1. `lhs.align_val() == rhs.align_val()`
2. `lhs.align_val() != rhs.align_val()`
