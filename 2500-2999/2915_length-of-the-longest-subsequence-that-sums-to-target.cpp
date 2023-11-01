#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    int lengthOfLongestSubsequence(std::vector<int> &nums, int target)
    {
        int n = nums.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(target + 1, -1));
        dp[0][0] = 0;
        if (nums[0] <= target)
            dp[0][nums[0]] = 1;
        for (int i = 1; i < n; ++i)
        {
            dp[i][0] = 0;
            for (int j = 1; j <= target; ++j)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i] && dp[i - 1][j - nums[i]] != -1)
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - nums[i]] + 1);
            }
        }
        debug::printVector2D(dp);
        return dp[n - 1][target] == 0 ? -1 : dp[n - 1][target];
    }
};

class Solution2
{
public:
    int lengthOfLongestSubsequence(std::vector<int> &nums, int target)
    {
        std::vector<int> dp(target + 1, -0x39c5bb);
        dp[0] = 0;
        int sum = 0;
        for (int num : nums)
        {
            sum += num;
            for (int j = std::min(sum, target); j >= num; --j)
                dp[j] = std::max(dp[j], dp[j - num] + 1);
        }
        return dp[target] > 0 ? dp[target] : -1;
    }
};


int main()
{
    Solution solution;
    std::vector<int> nums = {1, 3, 3, 8};
    int target = 7;
    int ans = solution.lengthOfLongestSubsequence(nums, target);
    logObj(ans);
    return 0;
}