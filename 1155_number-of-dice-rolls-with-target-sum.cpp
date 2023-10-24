#include <iostream>
#include <vector>

class Solution
{
public:
    int numRollsToTarget(int n, int k, int target)
    {
        const int MOD = 1e9 + 7;
        // dp[i][j]:投掷i次筛子，掷出和为j的方案数
        std::vector<int> dp(target + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = std::min(target, i * k); j >= 0; --j) // 终止条件必须是j>=0，因为要重置一些无效状态
            {
                dp[j] = 0;
                for (int p = 1; p <= k && j >= p; ++p)
                {
                    dp[j] = (dp[j] + dp[j - p]) % MOD;
                }
            }
        }

        return dp[target];
    }
};


int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}