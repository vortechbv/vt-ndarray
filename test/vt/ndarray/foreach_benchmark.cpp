// Copyright (c) 2018-2026 VORtech b.v.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <vt/ndarray.hpp>

#include <catch2/catch.hpp>

using std::size_t;

static float
sum(vt::ndview<const float, 1> x)
{
    const size_t n = x.shape(0);

    float sum_x = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        sum_x += x[i];
    }

    return sum_x;
}

static float
sum(vt::ndview<const float, 2> x)
{
    const size_t n = x.shape(0);
    const size_t m = x.shape(1);

    float sum_x = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            sum_x += x[i][j];
        }
    }

    return sum_x;
}

static float
sum(vt::ndview<const float, 3> x)
{
    const size_t n = x.shape(0);
    const size_t m = x.shape(1);
    const size_t p = x.shape(2);

    float sum_x = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            for (size_t k = 0; k < p; ++k) {
                sum_x += x[i][j][k];
            }
        }
    }

    return sum_x;
}

static float
sum(const vt::ndarray<float, 1>& x)
{
    const size_t n = x.shape(0);

    float sum_x = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        sum_x += x[i];
    }

    return sum_x;
}

static float
sum(const vt::ndarray<float, 2>& x)
{
    const size_t n = x.shape(0);
    const size_t m = x.shape(1);

    float sum_x = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            sum_x += x[i][j];
        }
    }

    return sum_x;
}

static float
sum(const vt::ndarray<float, 3>& x)
{
    const size_t n = x.shape(0);
    const size_t m = x.shape(1);
    const size_t p = x.shape(2);

    float sum_x = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            for (size_t k = 0; k < p; ++k) {
                sum_x += x[i][j][k];
            }
        }
    }

    return sum_x;
}

template<size_t N>
static float
iter_sum(vt::ndview<const float, N> x)
{
    float sum_x = 0.0f;
    for (float elem : x) {
        sum_x += elem;
    }

    return sum_x;
}

TEST_CASE("Benchmark sum", "[ndarray][!benchmark]") {
    const size_t n = GENERATE(8, 64, 512, 1024);

    SECTION("1D") {
        const vt::ndarray<float, 1> x{{ n }};

        BENCHMARK("Using vt::ndview") {
            return sum(x.view());
        };

        BENCHMARK("Using vt::ndarray") {
            return sum(x);
        };

        BENCHMARK("Using iterators") {
            return iter_sum<1>(x.view());
        };
    }

    SECTION("2D") {
        const vt::ndarray<float, 2> x{{ n, n }};

        BENCHMARK("Using vt::ndview") {
            return sum(x.view());
        };

        BENCHMARK("Using vt::ndarray") {
            return sum(x);
        };

        BENCHMARK("Using iterators") {
            return iter_sum<2>(x.view());
        };
    }

    SECTION("3D") {
        const vt::ndarray<float, 3> x{{ n, n, n }};

        BENCHMARK("Using vt::ndview") {
            return sum(x.view());
        };

        BENCHMARK("Using vt::ndarray") {
            return sum(x);
        };

        BENCHMARK("Using iterators") {
            return iter_sum<3>(x.view());
        };
    }
}
