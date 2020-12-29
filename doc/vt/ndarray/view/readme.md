vt::ndarray_view
================

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N>
class ndarray_view;
```

View into N-dimensional array data. It's essentially a pointer-shape pair for externally managed data, providing an N-dimensional `operator[]` interface. The data is assumed to be in row-major order and the view does not take ownership of the data.

For an owning N-dimensional array container, use [ndarray](../container/readme.md#top) instead.

This is a reference type and therefore cheap to copy, i.e. copy-constructing or assigning a view will be a shallow copy. As a reference type, note that `ndarray_view<const T, N>` is similar to `const T*`, while `const ndarray_view<T, N>` is similar to `T* const`.

Template parameters
-------------------

|||
----- | ---------------------------------------------------------------
**T** | the type of the elements in the data; possibly const-qualified
**N** | the number of dimensions; must be larger than 0

Member types
------------

Member type            | Definition
---------------------- | ----------
element_type           | `T`
value_type             | `std::remove_cv_t<T>`
index_type             | `std::size_t`
pointer                | `T*`
reference              | `T&`
iterator               | `T*`
const_iterator         | `const T*`
reverse_iterator       | `std::reverse_iterator<iterator>`
const_reverse_iterator | `std::reverse_iterator<const_iterator>`

Member constant
---------------

```c++
static constexpr std::size_t dim_count = N;
```

Member functions
----------------

|||
---------------------------------------------- | -------------------------------
[(constructor)](constructor.md#top)            | constructs a view
[operator[]](index-operator.md#top)            | accesses sub-views or elements
[operator ndarray_view](const-operator.md#top) | conversion to const-view
[element_count](element-count.md#top)          | returns the total number of elements
[shape](shape.md#top)                          | returns the N-dimensional shape
[reshape](reshape.md#top)                      | obtains a view with a different shape
[data](data.md#top)                            | returns a pointer to the first element
[slice](slice.md#top)                          | obtains a slice-view
[begin<br>cbegin](begin.md#top)                | returns an iterator to the beginning
[end<br>cend](end.md#top)                      | returns an iterator to the end
[rbegin<br>crbegin](rbegin.md#top)             | returns a reverse iterator to the beginning
[rend<br>crend](rend.md#top)                   | returns a reverse iterator to the end

Non-member functions
--------------------

|||
------------------------------------ | ----------------------
[operator<<](stream-operator.md#top) | performs stream output

Example
-------

```c++
#include <vt/ndarray/view.hpp>
#include <iostream>

int main()
{
    int data[6];
    // Creates a 2-dimensional array view into the data, with 2 rows and 3
    // columns:
    vt::ndarray_view<int, 2> view{{ 2, 3 }, data};

    view[0][0] = 3;
    view[0][1] = 1;
    view[0][2] = 4;
    view[1][0] = 1;
    view[1][1] = 5;
    view[1][2] = 9;

    std::cout << view << '\n';

    // Iterators iterate over the entire range of elements, regardless of
    // dimensionality:
    for (int i : view) {
        std::cout << i;
    }
    std::cout << '\n';

    // The ndarray_view is only a view into the original array, so changing
    // elements in the view will also change the corresponding elements in the
    // original array:
    for (int i : data) {
        std::cout << i;
    }
    std::cout << '\n';
}
```

Output:

```
[[3,1,4],[1,5,9]]
314159
314159
```
