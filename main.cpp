#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<int> nums = {18, 20, 2, 5, 8, 0, 21, 19, 7, 4, 13};
    kirie::nth_element(nums.begin(), nums.begin() + 5, nums.end());
    debug::printVector(nums);
    std::cout << kirie::max(39, 404) << std::endl;
    return 0;
}
