vt::ndarray_view::operator[]
============================

```c++
decltype(auto)
operator[](std::size_t idx) const noexcept;
```

Accesses the view or element at the specified index. The behavior is undefined if `idx >= shape[0]`.

Parameters
----------

|||
------- | --------------------------------------
**idx** | index of the view or element to access

Return value
------------

If `N > 1`, returns a view of dimension `N - 1` into the sub-array at the specified index.

If `N = 1`, returns a reference to the element at the specified index.
