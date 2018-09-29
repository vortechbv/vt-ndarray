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

static void
mul(
    vt::ndarray_view<const float, 2> A, vt::ndarray_view<const float, 2> B,
    vt::ndarray_view<float, 2> C)
{
    assert(A.shape(0) == C.shape(0));
    assert(A.shape(1) == B.shape(0));
    assert(B.shape(1) == C.shape(1));

    const size_t n = A.shape(0);
    const size_t m = A.shape(1);
    const size_t p = B.shape(1);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < p; ++j) {
            C[i][j] = 0.0f;
            for (size_t k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

static void
mul(
    const vt::ndarray<float, 2>& A, const vt::ndarray<float, 2>& B,
    vt::ndarray<float, 2>& C)
{
    assert(A.shape(0) == C.shape(0));
    assert(A.shape(1) == B.shape(0));
    assert(B.shape(1) == C.shape(1));

    const size_t n = A.shape(0);
    const size_t m = A.shape(1);
    const size_t p = B.shape(1);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < p; ++j) {
            C[i][j] = 0.0f;
            for (size_t k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

static void
mul(size_t n, size_t m, size_t p, const float* A, const float* B, float* C)
{
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < p; ++j) {
            C[i*p+j] = 0.0f;
            for (size_t k = 0; k < m; ++k) {
                C[i*p+j] += A[i*m+k] * B[k*p+j];
            }
        }
    }
}

static void
BM_naive_matrix_mul_ndarray_view(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 2> A{{ n, n }};
    const vt::ndarray<float, 2> B{{ n, n }};
    vt::ndarray<float, 2> C{{ n, n }};

    for (auto _ : state) {
        mul(A.view(), B.view(), C.view());
    }
}
BENCHMARK(BM_naive_matrix_mul_ndarray_view)->Range(8, 1024);

static void
BM_naive_matrix_mul_ndarray(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 2> A{{ n, n }};
    const vt::ndarray<float, 2> B{{ n, n }};
    vt::ndarray<float, 2> C{{ n, n }};

    for (auto _ : state) {
        mul(A, B, C);
    }
}
BENCHMARK(BM_naive_matrix_mul_ndarray)->Range(8, 1024);

static void
BM_naive_matrix_mul_pointers(benchmark::State& state)
{
    const size_t n = size_t(state.range(0));
    const vt::ndarray<float, 2> A{{ n, n }};
    const vt::ndarray<float, 2> B{{ n, n }};
    vt::ndarray<float, 2> C{{ n, n }};

    for (auto _ : state) {
        mul(n, n, n, A.data(), B.data(), C.data());
    }
}
BENCHMARK(BM_naive_matrix_mul_pointers)->Range(8, 1024);
