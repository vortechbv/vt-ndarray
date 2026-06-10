vt::ndview::ndview
==================

```c++
// (1)
constexpr ndview(const std::array<std::size_t, N>& shape, T* data) noexcept;
// (2)
template<ndview_compatible_range<T> R>
constexpr ndview(R&& r) noexcept requires(N == 1);
// (3)
constexpr ndview(
    std::initializer_list<std::remove_cv_t<T>> il
) noexcept requires(std::is_const_v<T> && N == 1);
```

Constructs a view from given data, a range or initializer list.

1. Constructs the view for the given shape over the given data. The behavior is undefined if the array pointed to by `data` contains less than `shape[0] * ... * shape[N-1]` elements.
2. Constructs the 1D view from the given contiguous range.
3. Constructs the 1D view from the given initializer list.

Parameters
----------

|||
--------- | --------------------------------------------------------------------
**shape** | an array containing the size of the data in each dimension
**data**  | a pointer to the array containing the data that is to be viewed into
**r**     | a contiguous range to view into
**il**    | an initializer list to view into

Example
-------

```c++
#include <vt/ndarray/view.hpp>
#include <iostream>

int sum(vt::ndview<const int, 1> x) {
    int sum_x = 0;
    for (int x_i : x) sum_x += x_i;
    return sum_x;
}

int main() {
    const std::array<int, 4> x = { 1, 2, 3, 4 };
    // A contiguous range, like std::array, can implicitly convert to a 1D
    // vt::ndview:
    std::cout << sum(x) << '\n';
}
```

Output:

```
10
```
