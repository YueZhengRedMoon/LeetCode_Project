#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    int findNumberOfLIS(std::vector<int> &nums)
    {
        int size = nums.size();

        // dp[i]:以nums[i]结尾的最长递增子序列的长度及其数量
        std::vector<std::vector<int>> dp(size, std::vector<int>(2, 1));

        int maxLen = 1;
        int count = 1;
        for (int i = 1; i < size; ++i)
        {
            if (dp[i][0] == maxLen)
            {
                ++count;
            }
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    int len = dp[j][0] + 1;
                    if (len > dp[i][0])
                    {
                        dp[i][0] = len;
                        dp[i][1] = dp[j][1];
                        if (dp[i][0] > maxLen)
                        {
                            maxLen = dp[i][0];
                            count = dp[i][1];
                        }
                        else if (dp[i][0] == maxLen)
                        {
                            count += dp[i][1];
                        }
                    }
                    else if (len == dp[i][0])
                    {
                        dp[i][1] += dp[j][1];
                        if (dp[i][0] == maxLen)
                        {
                            count += dp[j][1];
                        }
                    }
                }
            }
        }

        debug::printVector2D(dp);

        return count;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 2, 4, 3, 5, 4, 7, 2};
    std::vector<int> nums2 = {1,1,1,2,2,2,3,3,3};
    int count = solution.findNumberOfLIS(nums);
    std::cout << count << std::endl;
    return 0;
}
