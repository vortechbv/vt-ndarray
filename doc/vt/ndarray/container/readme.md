vt::ndarray
===========

- Defined in header `<vt/ndarray/container.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
// (1)
template<typename T, std::size_t N, typename Allocator = ndarray_allocator<T>>
class ndarray;
// (2)
namespace pmr {
    template<typename T, std::size_t N>
    using ndarray = vt::ndarray<T, N, std::pmr::polymorphic_allocator<T>>;
}
```

1. `vt::ndarray` is a container for an N-dimensional array that handles its storage automatically.
2. `vt::pmr::ndarray` is an alias template that uses a polymorphic allocator. (Only present if your standard library has `<memory_resource>`)

The array data is stored contiguously in row-major order.

For externally managed array data, use [ndview](../view/readme.md#top) instead.

Template parameters
-------------------

|||
------------- | ----------------------------------------------------------------
**T**         | the type of the elements; must not be cv-qualified
**N**         | the number of dimensions; must be larger than 0
**Allocator** | allocator for acquiring/releasing memory and constructing/destroying elements; `Allocator::value_type` must be the same as `T`

Member types
------------

Member type            | Definition
---------------------- | -----------------------------------------------
value_type             | `T`
allocator_type         | `Allocator`
size_type              | `std::size_t`
reference              | `T&`
const_reference        | `const T&`
pointer                | `T*`
const_pointer          | `const T*`
iterator               | `typename ndview<T, N>::iterator`
const_iterator         | `typename ndview<T, N>::const_iterator`
reverse_iterator       | `typename ndview<T, N>::reverse_iterator`
const_reverse_iterator | `typename ndview<T, N>::const_reverse_iterator`

Member constant
---------------

```c++
static constexpr std::size_t dim_count = N;
```

Member functions
----------------

|||
----------------------------------------------- | ----------------------------
[(constructor)](constructor.md#top)             | constructs the array
[(destructor)](destructor.md#top)               | destructs the array
[operator=](assign-operator.md#top)             | assigns an array
[operator[]](index-operator.md#top)             | accesses sub-views or elements
[operator ndview<br>view<br>cview](view.md#top) | conversion to view
[element_count](element-count.md#top)           | returns the total number of elements
[shape](shape.md#top)                           | returns the N-dimensional shape
[reshape](reshape.md#top)                       | obtains a view with a different shape
[flatten](flatten.md#top)                       | obtains a view with a flattened shape
[data](data.md#top)                             | direct access to the underlying array
[get_allocator](get_allocator.md#top)           | returns the associated allocator
[slice](slice.md#top)                           | obtains a slice-view
[begin<br>cbegin](begin.md#top)                 | returns an iterator to the beginning
[end<br>cend](end.md#top)                       | returns an iterator to the end
[rbegin<br>crbegin](rbegin.md#top)              | returns a reverse iterator to the beginning
[rend<br>crend](rend.md#top)                    | returns a reverse iterator to the end
[swap](swap.md#top)                             | swaps array contents

Non-member functions
--------------------

|||
-------------------------------------------------- | ----------------------
[operator==<br>operator!=](equals-operator.md#top) | compares the arrays
[operator<<](stream-operator.md#top)               | performs stream output
[swap](free-swap.md#top)                           | swaps array contents

[Deduction guides](deduction-guides.md#top)
-------------------------------------------

Example
-------

```c++
#include <vt/ndarray/container.hpp>
#include <iostream>

int main() {
    // Creates a 3-dimensional 2-by-3-by-4 array with the specified initial
    // values:
    const vt::ndarray<int, 3> a{{ 2, 3, 4 }, {
        000, 001, 002, 003,
        010, 011, 012, 013,
        020, 021, 022, 023,

        100, 101, 102, 103,
        110, 111, 112, 113,
        120, 121, 122, 123,
    }};

    std::cout << a << '\n';

    // The index-operator can be used to access elements:
    std::cout << a[0][2][3] << '\n';

    // The shape can be queried:
    std::cout << a.shape(0) << ',' << a.shape(1) << ',' a.shape(2) << '\n';

    // Iterators iterate over the entire range of elements, regardless of
    // dimensionality:
    for (int i : a) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
}
```

Output:

```
[[[0,1,2,3],[8,9,10,11],[16,17,18,19]],[[100,101,102,103],[110,111,112,113],[120,121,122,123]]]
19
2,3,4
 0 1 2 3 8 9 10 11 16 17 18 19 100 101 102 103 110 111 112 113 120 121 122 123
```
