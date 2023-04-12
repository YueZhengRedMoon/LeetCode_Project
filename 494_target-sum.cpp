#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int findTargetSumWays(std::vector<int> &nums, int target)
    {
        // 将nums分成两个集合positive和negative
        // positive集合中的元素加正号，negative集合中的元素加负号
        // 有positive - negative = target
        // 同时positive + negative = sum(nums)
        // 则positive = (sum + target) / 2
        // 背包的大小即为positive，问题转变为从nums中挑取若干个数，有多少种方法能凑成positive

        int sum = std::accumulate(nums.begin(), nums.end(), 0);

        int positive = (sum + target) / 2;
        if ((sum + target) % 2 != 0 || positive < 0)
        {
            // 如果不能整除，则说明凑不成target
            return 0;
        }


        // dp[j]:对于容量为j的背包，有多少种方法将其装满
        std::vector<int> dp(positive + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = positive; j >= nums[i]; --j)
            {
                dp[j] += dp[j - nums[i]];
            }
        }

        return dp[positive];
    }
};

int main()
{
    std::vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    Solution solution;
    std::cout << solution.findTargetSumWays(nums, target) << std::endl;
    return 0;
}
