#include <iostream>
#include <ctime>
#include <algorithm>

template <typename T>
void BlockMultiplication(T **A, T **B, T **C, size_t n, size_t m, size_t p, size_t b)
{
    for (size_t ii = 0; ii < n; ii += b)
        for (size_t jj = 0; jj < p; jj += b)
            for (size_t kk = 0; kk < m; kk += b)
                for (size_t i = ii; i < std::min(ii + b, n); ++i)
                    for (size_t j = jj; j < std::min(jj + b, p); ++j)
                        for (size_t k = kk; k < std::min(kk + b, m); ++k)
                            C[i][j] += A[i][k] * B[k][j];
}

void TestBlockMultiplication(size_t n, size_t m, size_t p, size_t b)
{
    double **A = new double *[n];
    double **B = new double *[m];
    double **C = new double *[n];

    for (size_t i = 0; i < n; ++i)
        A[i] = new double[m];
    for (size_t i = 0; i < m; ++i)
        B[i] = new double[p];
    for (size_t i = 0; i < n; ++i)
        C[i] = new double[p];

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            A[i][j] = 1.0;

    for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < p; ++j)
            B[i][j] = 1.0;

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < p; ++j)
            C[i][j] = 0.0;

    clock_t start = clock();
    BlockMultiplication(A, B, C, n, m, p, b);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time of execution for matrices of size " << n
              << "x" << m << " and " << m << "x" << p << " with block size " << b << ": "
              << elapsed << " seconds" << std::endl;

    for (size_t i = 0; i < n; ++i)
        delete[] A[i];
    for (size_t i = 0; i < m; ++i)
        delete[] B[i];
    for (size_t i = 0; i < n; ++i)
        delete[] C[i];
    delete[] A;
    delete[] B;
    delete[] C;
}