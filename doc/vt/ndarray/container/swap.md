vt::ndarray::swap
=================

```c++
void
swap(ndarray& other) noexcept;
```

Exchanges to shape and contents of the container with those of `other`. Does not invoke any move, copy or swap operations on individual elements.

Parameters
----------

|||
--------- | ---------------------------------------------
**other** | container to exchange shape and contents with
