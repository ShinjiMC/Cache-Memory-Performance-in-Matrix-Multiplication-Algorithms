#include <iostream>

const int MAX = 10000;
double A[MAX][MAX], x[MAX], y[MAX];

// Initialize the matrixs A and the vectors x and y
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

void first_loops()
{
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            y[i] += A[i][j] * x[j];
}

void second_loops()
{
    for (int j = 0; j < MAX; j++)
        for (int i = 0; i < MAX; i++)
            y[i] += A[i][j] * x[j];
}

int main()
{
    initialize();
    clock_t start1 = clock();
    first_loops();
    clock_t end1 = clock();
    double time1 = double(end1 - start1) / CLOCKS_PER_SEC;
    std::cout << "Time of the first pair of loops: " << time1
              << " seconds" << std::endl;
    for (int i = 0; i < MAX; i++)
        y[i] = 0;
    clock_t start2 = clock();
    second_loops();
    clock_t end2 = clock();
    double time2 = double(end2 - start2) / CLOCKS_PER_SEC;
    std::cout << "Time of the second pair of loops: " << time2
              << " seconds" << std::endl;
    return 0;
}
