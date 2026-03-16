vt::ndslice
===========

- Defined in header `<vt/ndarray/view.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N>
class ndslice;
```

View into non-contiguous N-dimensional array data. The slice does not take ownership of the data.

For an owning N-dimensional array container, use [ndarray](../container/readme.md#top) instead.

This is a reference type and therefore cheap to copy, i.e. copy-constructing or assigning a slice will be a shallow copy. As a reference type, note that `ndslice<const T, N>` is similar to `const T*`, while `const ndslice<T, N>` is similar to `T* const`.

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

Member constant
---------------

```c++
static constexpr std::size_t dim_count = N;
```

Member functions
----------------

|||
----------------------------------------- | ------------------------------------
[(constructor)](constructor.md#top)       | constructs a slice
[operator[]](index-operator.md#top)       | accesses sub-slices or elements
[operator ndslice](const-operator.md#top) | conversion to const-slice
[element_count](element-count.md#top)     | returns the total number of elements
[shape](shape.md#top)                     | returns the N-dimensional shape
[data](data.md#top)                       | returns a pointer to the first element

Non-member functions
--------------------

|||
------------------------------------ | ----------------------
[operator<<](stream-operator.md#top) | performs stream output

[Deduction guides](deduction-guides.md#top)
-------------------------------------------

Example
-------

```c++
#include <vt/ndarray/view.hpp>
#include <iostream>

int main() {
    int data[6] = {};
    // Creates a 2-dimensional array slice of the data, with 2 rows and 2
    // columns, and strides 3 and 1:
    vt::ndslice<int, 2> slice{{ 2, 2 }, { 3, 1 }, data};

    slice[0, 0] = 3;
    slice[0, 1] = 1;
    slice[1, 0] = 4;
    slice[1, 1] = 1;

    std::cout << slice << '\n';

    // The ndslice is only a view into the original array, so changing elements
    // in the slice will also change the corresponding elements in the original
    // array:
    for (int i : data) {
        std::cout << i;
    }
    std::cout << '\n';
}
```

Output:

```
[[3,1],[4,1]]
310410
```
