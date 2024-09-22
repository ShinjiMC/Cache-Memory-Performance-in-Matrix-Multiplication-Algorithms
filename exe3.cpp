#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <gtest/gtest.h>

template <typename T>
void multiplicacionBloques(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, std::vector<std::vector<T>> &C, size_t n, size_t m, size_t p, size_t b)
{
    for (size_t ii = 0; ii < n; ii += b)
        for (size_t jj = 0; jj < p; jj += b)
            for (size_t kk = 0; kk < m; kk += b)
                for (size_t i = ii; i < std::min(ii + b, n); ++i)
                    for (size_t j = jj; j < std::min(jj + b, p); ++j)
                        for (size_t k = kk; k < std::min(kk + b, m); ++k)
                            C[i][j] += A[i][k] * B[k][j];
}

void testMultiplicacionBloques(size_t n, size_t m, size_t p, size_t blockSize)
{
    std::vector<std::vector<double>> A(n, std::vector<double>(m, 1.0));
    std::vector<std::vector<double>> B(m, std::vector<double>(p, 1.0));
    std::vector<std::vector<double>> C(n, std::vector<double>(p, 0.0));

    auto start = std::chrono::high_resolution_clock::now();
    multiplicacionBloques(A, B, C, n, m, p, blockSize);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de ejecución para matrices de tamaño " << n << "x" << m << " y " << m << "x" << p << " con bloques de tamaño " << blockSize << ": "
              << elapsed.count() << " segundos" << std::endl;
}

TEST(MatrixMultiplicationTest, Matriz_10)
{
    EXPECT_NO_THROW(testMultiplicacionBloques(10, 10, 10, 2));
}

TEST(MatrixMultiplicationTest, Matriz_100)
{
    EXPECT_NO_THROW(testMultiplicacionBloques(100, 100, 100, 10));
}

TEST(MatrixMultiplicationTest, Matriz_500)
{
    EXPECT_NO_THROW(testMultiplicacionBloques(500, 500, 500, 50));
}

TEST(MatrixMultiplicationTest, Matriz_1000)
{
    EXPECT_NO_THROW(testMultiplicacionBloques(1000, 1000, 1000, 100));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
