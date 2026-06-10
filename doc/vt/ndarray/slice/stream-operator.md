operator<<(vt::ndslice)
=======================

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, ndslice<const T, N> a);
```

Inserts the formatted data of an `ndslice` into the specified output stream.

Parameters
----------

|||
------ | -----------------------------------------
**os** | the output stream to insert the data into
**a**  | the slice to insert

Return value
------------

Input parameter `os`.
