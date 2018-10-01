VT_CACHE_LINE_SIZE
==================

- Defined in header `<vt/ndarray/allocator.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
#ifndef VT_CACHE_LINE_SIZE
#   define VT_CACHE_LINE_SIZE 64
#endif
```

Unsigned integer value representing the cache-line size in bytes. This is used by `vt::ndarray_allocator` when determining a default alignment for allocations.

While the cache-line size can vary per machine, in practice the vast majority of modern systems have a cache-line size of 64 bytes. If 64 is not the correct value for your target hardware, you can override it by defining this macro to your desired value before including this library.
