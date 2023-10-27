#include <iostream>
#include <vector>

class Solution
{
public:
    int rob(std::vector<int> &nums)
    {
        // dpRob[i]:偷窃第i间房可以偷到的最大金额
        std::vector<int> dpRob(nums.size(), 0);
        dpRob[0] = nums[0];
        // dpNotRob[i]:不偷窃第i间房可以偷到的最大金额
        std::vector<int> dpNotRob(nums.size(), 0);

        for (int i = 1; i < nums.size(); ++i)
        {
            dpRob[i] = std::max(dpNotRob[i - 1] + nums[i], dpRob[i - 1]);
            dpNotRob[i] = std::max(dpRob[i - 1], dpNotRob[i - 1]);
        }

        return std::max(dpRob[nums.size() - 1], dpNotRob[nums.size() - 1]);
    }
};

class Solution2
{
public:
    int rob(std::vector<int> &nums)
    {
        if (nums.size() == 1)
            return nums[0];

        // dp[i]:偷窃0~i号房屋可以偷到的最大金额
        std::vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);

        for (int i = 2; i < nums.size(); ++i)
        {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[nums.size() - 1];
    }
};


int main()
{
    Solution2 solution;
    std::vector<int> nums = {1,2,3,1};
    std::cout << solution.rob(nums) << std::endl;
    return 0;
}