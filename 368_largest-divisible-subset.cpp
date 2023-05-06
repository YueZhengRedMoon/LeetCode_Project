#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    std::vector<int> largestDivisibleSubset(std::vector<int> &nums)
    {
        int numsSize = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> dp(numsSize);
        dp[0].push_back(nums[0]);
        int largestIndex = 0;
        int lasgestSize = 1;
        for (int i = 1; i < numsSize; ++i)
        {
            int index = -1;
            int size = 1;
            for (int j = i - 1; j >= 0; --j)
            {
                if (nums[i] % nums[j] == 0)
                {
                    int newSize = dp[j].size() + 1;
                    if (newSize > size)
                    {
                        index = j;
                        size = newSize;
                    }
                }
            }
            if (index == -1)
            {
                dp[i].push_back(nums[i]);
            }
            else
            {
                dp[i].resize(size);
                std::copy(dp[index].begin(), dp[index].end(), dp[i].begin());
                dp[i][size - 1] = nums[i];

                if (size > lasgestSize)
                {
                    lasgestSize = size;
                    largestIndex = i;
                }
            }
        }

        debug::printVector2D(dp);
        return dp[largestIndex];
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {4,8,10,240};
    std::vector<int> result = solution.largestDivisibleSubset(nums);
    std::cout << "result = ";
    debug::printVector(result);
    return 0;
}