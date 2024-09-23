#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

double **AllocateMatrix(size_t n)
{
    double **matrix = new double *[n];
    for (size_t i = 0; i < n; ++i)
        matrix[i] = new double[n];
    return matrix;
}

void InitializeMatrixRandom(double **matrix, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            matrix[i][j] = static_cast<double>(rand()) / RAND_MAX * 10.0;
}

void FreeMemoryMatrix(double **matrix, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

void ClassicMultiplication(double **A, double **B, double **C, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
        {
            C[i][j] = 0.0;
            for (size_t k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void BlockMultiplication(double **A, double **B, double **C, size_t n, size_t blockSize)
{
    for (size_t ii = 0; ii < n; ii += blockSize)
        for (size_t jj = 0; jj < n; jj += blockSize)
            for (size_t kk = 0; kk < n; kk += blockSize)
                for (size_t i = ii; i < std::min(ii + blockSize, n); ++i)
                    for (size_t j = jj; j < std::min(jj + blockSize, n); ++j)
                    {
                        double sum = 0.0;
                        for (size_t k = kk; k < std::min(kk + blockSize, n); ++k)
                            sum += A[i][k] * B[k][j];
                        C[i][j] += sum;
                    }
}

void RunTest(size_t n, size_t blockSize)
{
    double **A = AllocateMatrix(n);
    double **B = AllocateMatrix(n);
    double **C = AllocateMatrix(n);

    InitializeMatrixRandom(A, n);
    InitializeMatrixRandom(B, n);

    // Prueba de multiplicación clásica
    std::cout << "\nRunning Classic Multiplication..." << std::endl;
    clock_t start = clock();
    ClassicMultiplication(A, B, C, n);
    clock_t end = clock();
    double elapsedClassic = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Classic Multiplication Time: " << elapsedClassic << " seconds" << std::endl;

    // Prueba de multiplicación por bloques
    std::cout << "\nRunning Block Multiplication..." << std::endl;
    start = clock();
    BlockMultiplication(A, B, C, n, blockSize);
    end = clock();
    double elapsedBlock = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Block Multiplication Time: " << elapsedBlock << " seconds" << std::endl;

    FreeMemoryMatrix(A, n);
    FreeMemoryMatrix(B, n);
    FreeMemoryMatrix(C, n);
}

int main()
{
    size_t matrixSize = 2000;
    size_t blockSize = 64;

    std::cout << "Running test for matrix size: " << matrixSize << " and block size: " << blockSize << std::endl;
    RunTest(matrixSize, blockSize);

    return 0;
}
