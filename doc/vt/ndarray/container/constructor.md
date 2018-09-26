vt::ndarray::ndarray
====================

```c++
// (1)
ndarray() noexcept(noexcept(Allocator{}));
// (2)
explicit
ndarray(const Allocator& alloc) noexcept;
// (3)
explicit
ndarray(
    const std::array<std::size_t, N>& shape,
    const Allocator& alloc = Allocator{});
// (4)
ndarray(
    const std::array<std::size_t, N>& shape, const T& value,
    const Allocator& alloc = Allocator{});
// (5)
template<typename InputIt>
ndarray(
    const std::array<std::size_t, N>& shape,
    InputIt first, InputIt last,
    const Allocator& alloc = Allocator{});
// (6)
ndarray(
    const std::array<std::size_t, N>& shape,
    std::initializer_list<T> init,
    const Allocator& alloc = Allocator{});
// (7)
ndarray(const ndarray& other);
// (8)
ndarray(const ndarray& other, const Allocator& alloc);
// (9)
ndarray(ndarray&& other) noexcept;
// (10)
ndarray(ndarray&& other, const Allocator& alloc);
```

Constructs a new container from a variety of data sources, optionally using a user supplied allocator `alloc`.

1. Default constructor. Constructs an empty container, with a default-constructed allocator.
2. Constructs an empty container with the specified allocator.
3. Constructs the container with the specified shape and default-constructed elements.
4. Constructs the container with the specified shape, where all elements are copy-constructed from `value`.
5. Constructs the container with the specified shape and contents of the range `[first, last)`. The behavior is undefined if `std::distance(first, last)` is not equal to the number of elements in the container.
6. Constructs the container with the specifed shape and contents of the initializer list `init`. The behavior is undefined if `init.size()` is not equal to the number of elements in the container.
7. Copy constructor. Constructs the container with the shape and contents of `other`.
8. Allocator-extended copy constructor.
9. Move constructor. Constructs the container with the contents of `other` using move semantics. `other` is in a valid but unspecified state afterwards.
10. Allocator-extended move constructor.

Parameters
----------

|||
--------------- | -------------------------------------------------------------
**alloc**       | allocator to use for all memory allocations of this container
**shape**       | the N-dimensional shape of the array
**value**       | the value to initialize elements of the container with
**first, last** | the range to copy elements from
**init**        | initializer list to initialize elements of the container with
**other**       | another container to use as data source
