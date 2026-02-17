vt::ndarray::swap
=================

```c++
void swap(ndarray& other) noexcept;
```

Exchanges the shape and contents of the container with those of `other`. Does not invoke any move, copy or swap operations on individual elements.

If `std::allocator_traits<allocator_type>::propagate_on_container_swap::value` is `false` and if the allocators do not compare equal, the behavior is undefined.

Parameters
----------

|||
--------- | ---------------------------------------------
**other** | container to exchange shape and contents with
