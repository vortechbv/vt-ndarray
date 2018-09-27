vt::ndarray
===========

- Defined in header `<vt/ndarray/container.hpp>`
- Defined in header `<vt/ndarray.hpp>`

```c++
template<typename T, std::size_t N, typename Allocator = ndarray_allocator<T>>
class ndarray;
```

Container for a row-major N-dimensional array. It handles its storage automatically.

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
---------------------- | -----------------------------------------------------
value_type             | `T`
allocator_type         | `Allocator`
size_type              | `std::size_t`
reference              | `T&`
const_reference        | `const T&`
pointer                | `T*`
const_pointer          | `const T*`
iterator               | `typename ndarray_view<T, N>::iterator`
const_iterator         | `typename ndarray_view<T, N>::const_iterator`
reverse_iterator       | `typename ndarray_view<T, N>::reverse_iterator`
const_reverse_iterator | `typename ndarray_view<T, N>::const_reverse_iterator`

Member constant
---------------

```c++
static constexpr std::size_t dim_count = N;
```

Member functions
----------------

|||
------------------------------------------------------- | ----------------------
[(constructor)](constructor.md#top)                     | constructs the array
[(destructor)](destructor.md#top)                       | destructs the array
[operator=](assign-operator.md#top)                     | assigns an array
[operator[]](index-operator.md#top)                     | accesses sub-views or elements
[operator ndarray_view<br/>view<br/>cview](view.md#top) | conversion to view
[element_count](element-count.md#top)                   | returns the total number of elements
[shape](shape.md#top)                                   | returns the N-dimensional shape
[data](data.md#top)                                     | direct access to the underlying array
[get_allocator](get_allocator.md#top)                   | returns the associated allocator
[begin<br/>cbegin](begin.md#top)                        | returns an iterator to the beginning
[end<br/>cend](end.md#top)                              | returns an iterator to the end
[rbegin<br/>crbegin](rbegin.md#top)                     | returns a reverse iterator to the beginning
[rend<br/>crend](rend.md#top)                           | returns a reverse iterator to the end
[swap](swap.md#top)                                     | swaps array contents

Non-member functions
--------------------

|||
--------------------------------------------------- | -----------------------
[operator==<br/>operator!=](equals-operator.md#top) | compares the arrays
[operator<<](stream-operator.md#top)                | performs stream output
[swap](free-swap.md#top)                            | swaps array contents

Example
-------

```c++
#include <vt/ndarray/container.hpp>
#include <iostream>

int main()
{
    // Creates a 3-dimensional 2-by-3-by-4 array with the specified initial
    // values:
    const vt::ndarray<int, 3> a{{ 2, 3, 4 }, {
        3, 1, 4, 1,
        5, 9, 2, 6,
        5, 3, 5, 8,

        9, 7, 9, 3,
        2, 3, 8, 4,
        6, 2, 6, 4
    }};

    std::cout << a << '\n';

    // The index-operator can be used to access elements:
    std::cout << a[0][2][3] << '\n';

    // The shape can be queried:
    std::cout << a.shape(0) << ',' << a.shape(1) << ',' a.shape(2) << '\n';

    // Iterators iterate over the entire range of elements, regardless of
    // dimensionality:
    for (int i : a) {
        std::cout << i;
    }
    std::cout << '\n';
}
```

Output:

```
[[[3,1,4,1],[5,9,2,6],[5,3,5,8]],[[9,7,9,3],[2,3,8,4],[6,2,6,4]]]
8
2,3,4
314159265358979323846264
```
