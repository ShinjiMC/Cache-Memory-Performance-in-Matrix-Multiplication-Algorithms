#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

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

void RunTest(size_t n)
{
    double **A = AllocateMatrix(n);
    double **B = AllocateMatrix(n);
    double **C = AllocateMatrix(n);

    InitializeMatrixRandom(A, n);
    InitializeMatrixRandom(B, n);

    clock_t start = clock();
    ClassicMultiplication(A, B, C, n);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time of execution for matrices of size " << n
              << "x" << n << ": " << elapsed << " seconds" << std::endl;

    FreeMemoryMatrix(A, n);
    FreeMemoryMatrix(B, n);
    FreeMemoryMatrix(C, n);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <matrix size | test>" << std::endl;
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "test")
    {
        std::vector<size_t> testSizes = {100, 200, 500, 1000, 2000};
        for (size_t n : testSizes)
        {
            std::cout << "\nRunning test for matrix size: " << n << std::endl;
            RunTest(n);
        }
    }
    else
    {
        size_t n;
        try
        {
            n = std::stoi(arg);
        }
        catch (const std::invalid_argument &)
        {
            std::cerr << "Invalid argument. Please provide a valid number or 'test'." << std::endl;
            return 1;
        }

        std::cout << "\nRunning test for matrix size: " << n << std::endl;
        RunTest(n);
    }

    return 0;
}
