vt::ndarray_allocator
=====================

- Defined in header `<vt/ndarray/allocator.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T>
class ndarray_allocator;
```

The default allocator for the [ndarray](../container/readme.md#top) class. It differs from `std::allocator` in two ways:

- It doesn't zero-initialize fundamental types when default constructing them.
- It aligns allocations to the cache-line size or a user-specified alignment value.

Instances of this allocator are interchangeable if their alignment value matches.

Template parameters
-------------------

|||
----- | ------------------------------------------------------------------------
**T** | the type of elements of arrays this allocator allocates; must not be cv-qualified

Member types
------------

Member type                            | Definition
-------------------------------------- | ----------------
value_type                             | `T`
propagate_on_container_move_assignment | `std::true_type`
propagate_on_container_swap            | `std::true_type`

Member functions
----------------

|||
----------------------------------- | -----------------------------------------
[(constructor)](constructor.md#top) | creates a new allocator instance
[allocate](allocate.md#top)         | allocates uninitialized storage
[deallocate](deallocate.md#top)     | deallocates storage
[construct](construct.md#top)       | constructs an object in allocated storage
[destroy](destroy.md#top)           | destructs an object in allocated storage
[align_val](align-val.md#top)       | returns the alignment value

Non-member functions
--------------------

|||
--------------------------------------------------- | -----------------------
[operator==<br/>operator!=](equals-operator.md#top) | compares two allocators

Macros
------

|||
-------------------------------------------- | ---------------------------------
[VT_CACHE_LINE_SIZE](cache-line-size.md#top) | user-overridable cache-line size constant
