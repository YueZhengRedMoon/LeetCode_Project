#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    bool canPartition(std::vector<int> &nums)
    {
        if (nums.size() <= 1)
        {
            return false;
        }

        int sum = 0;
        for (int num : nums)
        {
            sum += num;
        }

        // 总和为奇数，一定不可能分成两个子集，使得它们的和相等
        if (sum % 2 != 0)
        {
            return false;
        }

        int target = sum / 2;
        // dp[i][j]:从nums[0:i]中可以任取若干个数，它们的和为j
        std::vector<std::vector<bool>> dp(nums.size(), std::vector<bool>(sum + 1, false));

        for (int i = 0; i < nums.size(); ++i)
        {
            for (int k = i; k < nums.size(); ++k)
            {
                dp[k][nums[i]] = true;
                if (nums[i] == target)
                {
                    return true;
                }
                if (nums[i] > target)
                {
                    return false;
                }
            }
        }

        for (int i = 1; i < nums.size(); ++i)
        {
            for (int j = 0; j <= sum; ++j)
            {
                if (!dp[i][j])
                {
                    if (j >= nums[i])
                    {
                        dp[i][j] = dp[i - 1][j - nums[i]] || dp[i - 1][j];
                    }
                    else
                    {
                        dp[i][j] = dp[i - 1][j];
                    }
                }
            }
            if (dp[i][target])
            {
                return true;
            }
        }
        return false;
    }
};

class Solution2
{
public:
    bool canPartition(std::vector<int> &nums)
    {
        int sum = 0;
        sum = std::accumulate(nums.begin(), nums.end(), 0);

        if (sum % 2 != 0)
        {
            return false;
        }

        int target = sum / 2;
        // dp[j]:对于容量为j的背包，最多能放多大价值的物品
        std::vector<int> dp(target + 1, 0);

        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = target; j >= nums[i]; --j)
            {
                dp[j] = std::max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }

        return dp[target] == target;
    }
};

int main()
{
    std::vector<int> nums = {99, 1};
    Solution solution;
    if (solution.canPartition(nums))
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }
    return 0;
}