vt::ndview_compatible_range
===========================

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename R, typename T>
concept ndview_compatible_range =
    std::is_convertible_v<
        std::remove_reference_t<std::ranges::range_reference_t<R>>(*)[],
        T(*)[]
    >
    && std::ranges::contiguous_range<R>
    && std::ranges::sized_range<R>
    && (std::ranges::borrowed_range<R> || std::is_const_v<T>)
    && !is_ndview_v<R>;
```

The concept `ndview_compatible_range<R, T>` specifies that `R` is a contiguous range of elements of type `T` that a `vt::ndview`/`vt::ndslice` can be constructed for.
