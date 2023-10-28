#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include "../debug/debug.h"

class Solution
{
public:
    int maxSumDivThree(std::vector<int> &nums)
    {
        const int ninf = std::numeric_limits<int>::min();
        // dp[i][j]:nums[0:i]中能余j的最大和
        std::array<int, 3u> dp = {0, ninf, ninf};
        for (int num : nums)
        {
            std::array<int, 3u> cur = dp;
            int mod = num % 3;
            for (int j = 0; j < 3; ++j)
            {
                cur[j] = std::max(cur[j], dp[(j + 3 - mod) % 3] + num);
            }
            dp = cur;
            debug::printIterRange(dp.begin(), dp.end());
        }
        return dp[0];
    }
};

class Solution2
{
public:
    int maxSumDivThree(std::vector<int> &nums)
    {
        const int ninf = std::numeric_limits<int>::min();
        std::vector<int> dp{0, ninf, ninf};
        for (int num : nums)
        {
            std::vector<int> cur = dp;
            for (int i = 0; i < 3; ++i)
            {
                cur[(i + num % 3) % 3] = std::max(cur[(i + num % 3) % 3], dp[i] + num);
            }
            dp = std::move(cur);
            debug::printIterRange(dp.begin(), dp.end());
        }
        return dp[0];
    }
};

int main()
{
    Solution2 solution;
    std::vector<int> nums = {3,6,5,1,8};
    int ans = solution.maxSumDivThree(nums);
    std::cout << ans << std::endl;
    return 0;
}