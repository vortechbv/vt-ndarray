vt::ndarray_allocator::ndarray_allocator
========================================

```c++
// (1)
constexpr
ndarray_allocator() noexcept;
// (2)
explicit constexpr
ndarray_allocator(std::align_val_t align_val) noexcept;
// (3)
template<typename U>
constexpr
ndarray_allocator(const ndarray_allocator<U>& other) noexcept;
```

Constructs the allocator.

1. Uses a default alignment value, which is either the cache-line size or `alignof(T)`.
2. Uses the specified alignment value for all allocations by this allocator. The behavior is undefined if `align_val < alignof(T)` or if `align_val` is not a valid alignment value.
3. Copies the alignment value from `other`.

Parameters
----------

|||
-------------- | -----------------------------------
**align\_val** | alignment to use
**other**      | another allocator to construct with
