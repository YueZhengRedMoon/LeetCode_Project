#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int coinChange(std::vector<int> &coins, int amount)
    {
        // dp[i]:凑成面值i最少需要多少枚硬币
        const int inf = std::numeric_limits<int>::max() - 1;
        std::vector<int> dp(amount + 1, inf);
        dp[0] = 0;

        for (int i = 0; i < coins.size(); ++i)
        {
            for (int j = coins[i]; j <= amount; ++j)
            {
                dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
            }
        }

        return dp[amount] == inf ? -1 : dp[amount];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}