#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <gtest/gtest.h>

// Multiplicación por bloques
template <typename T>
void multiplicacionBloques(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, std::vector<std::vector<T>> &C, size_t n, size_t m, size_t p, size_t b)
{
    // Inicializar la matriz C a ceros
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < p; ++j)
            C[i][j] = 0;

    // Multiplicación por bloques
    for (size_t ii = 0; ii < n; ii += b)
        for (size_t jj = 0; jj < p; jj += b)
            for (size_t kk = 0; kk < m; kk += b)
                for (size_t i = ii; i < std::min(ii + b, n); ++i)
                    for (size_t j = jj; j < std::min(jj + b, p); ++j)
                        for (size_t k = kk; k < std::min(kk + b, m); ++k)
                            C[i][j] += A[i][k] * B[k][j];
}

// Multiplicación clásica para comparación
template <typename T>
void multiplicacionClasica(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, std::vector<std::vector<T>> &C, size_t n, size_t m, size_t p)
{
    // Inicializar la matriz C a ceros
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < p; ++j)
            C[i][j] = 0;

    // Multiplicación clásica
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < p; ++j)
            for (size_t k = 0; k < m; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

// Función para probar la multiplicación por bloques
void testMultiplicacionBloques(size_t n, size_t m, size_t p, size_t blockSize)
{
    std::vector<std::vector<double>> A(n, std::vector<double>(m, 1.0));
    std::vector<std::vector<double>> B(m, std::vector<double>(p, 1.0));
    std::vector<std::vector<double>> C(n, std::vector<double>(p, 0.0));
    std::vector<std::vector<double>> C_clasica(n, std::vector<double>(p, 0.0));

    // Multiplicación clásica
    multiplicacionClasica(A, B, C_clasica, n, m, p);

    // Multiplicación por bloques
    multiplicacionBloques(A, B, C, n, m, p, blockSize);

    // Comprobar si los resultados son iguales
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < p; ++j)
        {
            ASSERT_NEAR(C[i][j], C_clasica[i][j], 1e-9) << "Error en la posición (" << i << ", " << j << ")";
        }
    }
}

// Pruebas con GTest
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
