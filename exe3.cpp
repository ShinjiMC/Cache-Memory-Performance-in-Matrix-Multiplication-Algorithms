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

    clock_t start = clock();
    BlockMultiplication(A, B, C, n, blockSize);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time of execution for matrices of size " << n
              << "x" << n << " with block size " << blockSize << ": "
              << elapsed << " seconds" << std::endl;

    FreeMemoryMatrix(A, n);
    FreeMemoryMatrix(B, n);
    FreeMemoryMatrix(C, n);
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <matrix size> <block size> | test" << std::endl;
        return 1;
    }

    std::string arg = argv[1];

    if (arg == "test")
    {
        std::vector<size_t> testSizes = {100, 200, 500, 1000, 2000};
        std::vector<size_t> blockSizes = {8, 8, 16, 32, 64}; // Block size for test cases

        for (size_t i = 0; i < testSizes.size(); ++i)
        {
            std::cout << "\nRunning test for matrix size: " << testSizes[i]
                      << " and block size: " << blockSizes[i] << std::endl;
            RunTest(testSizes[i], blockSizes[i]);
        }
    }
    else
    {
        size_t n, blockSize;
        try
        {
            n = std::stoi(arg);
            blockSize = std::stoi(argv[2]);
        }
        catch (const std::invalid_argument &)
        {
            std::cerr << "Invalid argument. Please provide valid numbers for matrix size and block size, or 'test'." << std::endl;
            return 1;
        }

        std::cout << "\nRunning test for matrix size: " << n
                  << " and block size: " << blockSize << std::endl;
        RunTest(n, blockSize);
    }

    return 0;
}
