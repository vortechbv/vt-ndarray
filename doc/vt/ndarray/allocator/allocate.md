vt::ndarray_allocator::allocate
===============================

```c++
[[nodiscard]] T* allocate(std::size_t n) const;
```

Allocates `n * sizeof(T)` bytes of uninitialized storage, aligned to [align_val()](align-val.md#top).

Parameters
----------

|||
----- | ---------------------------------------------
**n** | the number of objects to allocate storage for

Return value
------------

Pointer to the first byte of the allocated memory block.

Exceptions
----------

Throws `std::bad_alloc` if allocation fails.
