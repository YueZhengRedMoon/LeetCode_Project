#include <iostream>
#include <vector>

class Solution
{
public:
    long long maxAlternatingSum(std::vector<int> &nums)
    {
        // dp[i][0]:nums[0:i]长度为偶数的最大子序列交替和
        // dp[i][1]:nums[0:i]长度为奇数的最大子序列交替和
        // dp[i][0] = max(dp[i-1][1] + nums[i], dp[i-1][0])
        // dp[i][1] = max(dp[i-1][0] - nums[i], dp[i-1][1]

        std::pair<long long, long long> dp;
        dp.first = nums[0];
        dp.second = 0;

        for (int i = 1; i < nums.size(); ++i)
        {
            std::pair<long long, long long> last(dp);
            dp.first = std::max(last.second + nums[i], last.first);
            dp.second = std::max(last.first - nums[i], last.second);
        }

        return std::max(dp.first, dp.second);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
