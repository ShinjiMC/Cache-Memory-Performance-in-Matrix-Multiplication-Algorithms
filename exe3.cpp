#include "Blocks.hpp"
#include <vector>

int main()
{
    std::vector<size_t> nums = {10, 100, 500, 1000};
    std::vector<size_t> blocks = {2, 10, 50, 100};
    for (auto a = 0; a < 4; a++)
        TestBlockMultiplication(nums[a], nums[a], nums[a], blocks[a]);
    return 0;
}