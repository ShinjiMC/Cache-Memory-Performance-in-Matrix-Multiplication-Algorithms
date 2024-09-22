#include <iostream>
#include <chrono>

const int MAX = 10000;
double A[MAX][MAX], x[MAX], y[MAX];

// Inicializa A y x, asigna y = 0
void initialize()
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
            A[i][j] = i + j;
        x[i] = i;
        y[i] = 0;
    }
}

// Primer par de bucles
void first_loops()
{
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A[i][j] * x[j];
}

// Segundo par de bucles
void second_loops()
{
    for (int j = 0; j < MAX; j++)
        for (int i = 0; i < MAX; i++)
            y[i] += A[i][j] * x[j];
}

int main()
{
    initialize();

    auto start1 = std::chrono::high_resolution_clock::now();
    first_loops();
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time1 = end1 - start1;
    std::cout << "Tiempo del primer par de bucles: " << time1.count() << " segundos" << std::endl;
    for (int i = 0; i < MAX; i++)
        y[i] = 0;
    auto start2 = std::chrono::high_resolution_clock::now();
    second_loops();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time2 = end2 - start2;
    std::cout << "Tiempo del segundo par de bucles: " << time2.count() << " segundos" << std::endl;
    return 0;
}
