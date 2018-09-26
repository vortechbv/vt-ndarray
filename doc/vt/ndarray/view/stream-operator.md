operator<<(vt::ndarray_view)
============================

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N>
std::ostream&
operator<<(std::ostream& os, ndarray_view<const T, N> a);
```

Inserts the formatted data of an `ndarray_view` into the specified output stream.

Parameters
----------

|||
------ | -----------------------------------------
**os** | the output stream to insert the data into
**a**  | the view to insert

Return value
------------

Input parameter `os`.
