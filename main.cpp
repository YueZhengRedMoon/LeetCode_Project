#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_set>
#include "kirie_algorithm.h"
#include "debug.h"

int main()
{
    std::vector<int> nums = {9, 12, 6, 1, 4, 7, 8, 20, 3};
    kirie::heapify(nums, std::less<>());
    debug::printVector(nums);
    kirie::heapify(nums, std::greater<>());
    debug::printVector(nums);
    return 0;
}
