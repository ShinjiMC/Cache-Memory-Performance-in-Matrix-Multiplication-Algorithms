#include <iostream>
#include <chrono>
#include <vector>
#include <gtest/gtest.h>

template <typename T>
void multiplicacion(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, std::vector<std::vector<T>> &C, size_t n, size_t m, size_t p)
{
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < p; ++j)
            for (size_t k = 0; k < m; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

void testMultiplicacion(size_t n, size_t m, size_t p)
{
    std::vector<std::vector<double>> A(n, std::vector<double>(m, 1.0));
    std::vector<std::vector<double>> B(m, std::vector<double>(p, 1.0));
    std::vector<std::vector<double>> C(n, std::vector<double>(p, 0.0));

    auto start = std::chrono::high_resolution_clock::now();
    multiplicacion(A, B, C, n, m, p);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Tiempo de ejecución para matrices de tamaño " << n << "x" << m << " y " << m << "x" << p << ": "
              << elapsed.count() << " segundos" << std::endl;
}

TEST(MatrixMultiplicationTest, Matriz_10)
{
    EXPECT_NO_THROW(testMultiplicacion(10, 10, 10));
}

TEST(MatrixMultiplicationTest, Matriz_100)
{
    EXPECT_NO_THROW(testMultiplicacion(100, 100, 100));
}

TEST(MatrixMultiplicationTest, Matriz_500)
{
    EXPECT_NO_THROW(testMultiplicacion(500, 500, 500));
}

TEST(MatrixMultiplicationTest, Matriz_1000)
{
    EXPECT_NO_THROW(testMultiplicacion(1000, 1000, 1000));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}