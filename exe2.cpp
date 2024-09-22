#include "Classic.hpp"

int main()
{
    auto nums = {10, 100, 500, 1000};
    for (auto n : nums)
        TestClassicMultiplication(n, n, n);
    return 0;
}