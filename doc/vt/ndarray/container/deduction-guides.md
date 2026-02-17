deduction guides for vt::ndarray
================================

- Defined in header `<vt/ndarray/container.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
// (1)
template<typename T, std::size_t N, typename Allocator = ndarray_allocator<T>>
ndarray(
    const std::size_t (&)[N],
    const T&,
    Allocator = Allocator()
) -> ndarray<T, N, Allocator>;
// (2)
template<
    typename InputIt,
    std::size_t N,
    typename Allocator = ndarray_allocator<typename std::iterator_traits<InputIt>::value_type>
>
ndarray(
    const std::size_t (&)[N],
    InputIt,
    InputIt,
    Allocator = Allocator()
) -> ndarray<typename std::iterator_traits<InputIt>::value_type, N, Allocator>;
// (3)
template<typename T, std::size_t N, typename Allocator = ndarray_allocator<T>>
ndarray(
    const std::size_t (&)[N],
    std::initializer_list<T>,
    Allocator = Allocator()
) -> ndarray<T, N, Allocator>;
```

This deduction guide is provided for `ndarray` to allow deduction from an array literal as `shape` argument, with overloads:

1. For the fill-constructor.
2. For the iterator-pair constructor.
3. For the initializer-list constructor.

Example
-------

```c++
#include <vt/ndarray/container.hpp>

int main() {
    // Uses explicit deduction guide to deduce vt::ndarray<int, 2>
    vt::ndarray array{{ 2, 2 }, 42};
}
```
