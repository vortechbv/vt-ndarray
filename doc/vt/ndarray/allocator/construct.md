vt::ndarray_allocator::construct
================================

```c++
template<typename U>
void construct(U* p) const noexcept(std::is_nothrow_default_constructible_v<U>);
```

Default-constructs an object of type `U` in allocated uninitialized storage pointed to by `p`, unless `U` is a fundamental type. In the latter case, this will be a no-op.

Parameters
----------

|||
----- | ------------------------------------------
**p** | pointer to allocated uninitialized storage

Notes
-----

The behavior of this function means that fundamental types (`int`, `float`, etc.) will not be zero-initialized when default-constructed. This makes the behavior of this allocator more similar to `new T[n]` than `std::allocator<T>`.
