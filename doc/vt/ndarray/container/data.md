vt::ndarray::data
=================

```c++
T* data() noexcept;
const T* data() const noexcept;
```

Returns a pointer to the underlying array serving as element storage. May return `nullptr` if the container is empty.

Return value
------------

Pointer to the underlying array.
