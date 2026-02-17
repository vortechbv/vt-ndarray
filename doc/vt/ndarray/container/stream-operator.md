operator<<(vt::ndarray)
=======================

- Defined in header `<vt/ndarray/container.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N, typename Allocator>
std::ostream& operator<<(std::ostream& os, const ndarray<T, N, Allocator>& a);
```

Inserts the formatted data of an `ndarray` into the specified output stream.

Parameters
----------

|||
------ | -----------------------------------------
**os** | the output stream to insert the data into
**a**  | the array to insert

Return value
------------

Input parameter `os`.
