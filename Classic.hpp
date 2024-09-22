#include <iostream>
#include <ctime>

template <typename T>
void ClassicMultiplication(T **A, T **B, T **C, size_t n, size_t m, size_t p)
{
    // Multiplicar A y B
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < p; ++j)
            for (size_t k = 0; k < m; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

void TestClassicMultiplication(size_t n, size_t m, size_t p)
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
    ClassicMultiplication(A, B, C, n, m, p);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time of execution for matrices of size " << n
              << "x" << m << " and " << m << "x" << p << ": "
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