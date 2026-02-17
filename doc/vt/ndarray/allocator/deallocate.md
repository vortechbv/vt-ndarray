vt::ndarray_allocator::deallocate
=================================

```c++
void deallocate(T* p, std::size_t n) const noexcept;
```

Deallocates the storage referenced by the pointer `p`, which must be a pointer obtained by an earlier call to [allocate()](allocate.md#top).

The argument `n` must be equal to the first argument of the call to [allocate()](allocate.md#top) that originally produced `p`; otherwise, the behavior is undefined.

Parameters
----------

|||
----- | ---------------------------------------------
**p** | pointer obtained from `allocate()`
**n** | number of objects earlier passed to `allocate()`
