vt::ndarray_allocator::destroy
==============================

```c++
template<typename U>
void
destroy(U* p) const noexcept(std::is_nothrow_destructible_v<U>);
```

Calls the destructor of the object pointed to by `p`.

Parameters
----------

|||
----- | ---------------------------------------------------
**p** | pointer to the object that is going to be destroyed
