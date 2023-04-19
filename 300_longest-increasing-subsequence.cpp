#include <iostream>
#include <vector>

class Solution
{
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        // dp[i]:nums[0:i]中以nums[i]结尾的最长严格递增子序列的长度
        std::vector<int> dp(nums.size(), 0);
        dp[0] = 1;
        int result = 1;

        for (int i = 1; i < nums.size(); ++i)
        {
            dp[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            if (dp[i] > result)
                result = dp[i];
        }

        return result;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
