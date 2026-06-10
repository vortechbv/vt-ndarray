vt::indexer
===========

- Defined in header `<vt/ndarray/index.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T>
concept indexer =
    std::convertible_to<T, std::size_t>
    || std::is_same_v<T, vt::index_range<0>>
    || std::is_same_v<T, vt::index_range<1>>
    || std::is_same_v<T, vt::index_range<2>>;
```

The concept `indexer<T>` specifies that `T` is an object type that can be used to index into a `vt::ndview`/`vt::ndslice`/`vt::ndarray`.
