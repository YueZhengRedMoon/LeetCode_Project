#include <iostream>
#include <vector>

class Solution
{
public:
    int maxProfit(std::vector<int> &prices)
    {
        // dp[0]:第一次持有股票时的最大利润
        // dp[1]:第一次不持有股票时的最大利润
        // dp[2]:第二次持有股票时的最大利润
        // dp[3]:第二次不持有股票时的最大利润
        int dp[4] = {0};
        dp[0] = -prices[0]; // 第一天买入
        dp[2] = -prices[0]; // 第一天，先买入，再卖出，再买入
        for (int i = 1; i < prices.size(); ++i)
        {
            dp[0] = std::max(dp[0], -prices[i]);
            dp[1] = std::max(dp[1], dp[0] + prices[i]);
            dp[2] = std::max(dp[2], dp[1] - prices[i]);
            dp[3] = std::max(dp[3], dp[2] + prices[i]);
        }

        return dp[3];
    }
};

int main()
{
    std::vector<int> prices = {3,3,5,0,0,3,1,4};
    Solution solution;
    std::cout << solution.maxProfit(prices) << std::endl;
    return 0;
}
