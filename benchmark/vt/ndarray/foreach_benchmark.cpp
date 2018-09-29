// Copyright (c) 2018 VORtech b.v.
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

#include <benchmark/benchmark.h>
#include <cassert>

using std::size_t;

static float
sum(vt::ndarray_view<const float, 1> x)
{
    const size_t n = x.shape(0);

    float sum_x = 0.0f;
    for (size_t i = 0; i < n; ++i) {
        sum_x += x[i];
    }

    return sum_x;
}

static float
sum(vt::ndarray_view<const float, 2> x)
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
sum(vt::ndarray_view<const float, 3> x)
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
iter_sum(vt::ndarray_view<const float, N> x)
{
    float sum_x = 0.0f;
    for (float elem : x) {
        sum_x += elem;
    }

    return sum_x;
}

static void
BM_sum_1d_ndarray_view(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 1> x{{ n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(x.view()));
    }
}
BENCHMARK(BM_sum_1d_ndarray_view)->Range(8, 1024);

static void
BM_sum_2d_ndarray_view(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 2> x{{ n, n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(x.view()));
    }
}
BENCHMARK(BM_sum_2d_ndarray_view)->Range(8, 1024);

static void
BM_sum_3d_ndarray_view(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 3> x{{ n, n, n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(x.view()));
    }
}
BENCHMARK(BM_sum_3d_ndarray_view)->Range(8, 1024);

static void
BM_sum_1d_ndarray(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 1> x{{ n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(x));
    }
}
BENCHMARK(BM_sum_1d_ndarray)->Range(8, 1024);

static void
BM_sum_2d_ndarray(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 2> x{{ n, n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(x));
    }
}
BENCHMARK(BM_sum_2d_ndarray)->Range(8, 1024);

static void
BM_sum_3d_ndarray(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 3> x{{ n, n, n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(x));
    }
}
BENCHMARK(BM_sum_3d_ndarray)->Range(8, 1024);

static void
BM_sum_1d_iterators(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 1> x{{ n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(iter_sum<1>(x));
    }
}
BENCHMARK(BM_sum_1d_iterators)->Range(8, 1024);

static void
BM_sum_2d_iterators(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 2> x{{ n, n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(iter_sum<2>(x));
    }
}
BENCHMARK(BM_sum_2d_iterators)->Range(8, 1024);

static void
BM_sum_3d_iterators(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 3> x{{ n, n, n }};

    for (auto _ : state) {
        benchmark::DoNotOptimize(iter_sum<3>(x));
    }
}
BENCHMARK(BM_sum_3d_iterators)->Range(8, 1024);
