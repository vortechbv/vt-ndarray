vt::ndarray::operator=
======================

```c++
// (1)
ndarray& operator=(const ndarray& other);
// (2)
ndarray& operator=(ndarray&& other);
```

Replaces the contents of the container.

1. Copy assignment operator. Replaces the shape and contents with a copy of the contents of `other`.
2. Move assignment operator. Replaces the shape and contents with those of `other` using move semantics. `other` is in a valid but unspecified state afterwards.

Parameters
----------

|||
--------- | ---------------------------------------
**other** | another container to use as data source

Return value
------------

Returns `*this`.
