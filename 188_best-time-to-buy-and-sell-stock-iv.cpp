#include <iostream>
#include <vector>

class Solution
{
public:
    int maxProfit(int k, std::vector<int> &prices)
    {
        // i:[1, k]
        // dp[2 * i - 1]:第i次持有股票时的最大利润
        // dp[2 * i]:第i次不持有股票时的最大利润
        std::vector<int> dp(2 * k + 1, 0);
        for (int i = 1; i <= k; ++i)
        {
            dp[2 * i - 1] = -prices[0];
        }

        for (int i = 1; i < prices.size(); ++i)
        {
            for (int j = 1; j <= k; ++j)
            {
                dp[2 * j - 1] = std::max(dp[2 * j - 1], dp[2 * (j - 1)] - prices[i]);
                dp[2 * j] = std::max(dp[2 * j], dp[2 * j - 1] + prices[i]);
            }
        }

        return dp[2 * k];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}