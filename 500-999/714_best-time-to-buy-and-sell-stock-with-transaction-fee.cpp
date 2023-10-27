#include <iostream>
#include <vector>

class Solution
{
public:
    int maxProfit(std::vector<int> &prices, int fee)
    {
        // dp[i].first:第i天持有股票时的最大利润
        // dp[i].second:第i天不持有股票时的最大利润
        std::vector<std::pair<int, int>> dp(2);
        dp[0].first = -prices[0] - fee;

        for (int i = 1; i < prices.size(); ++i)
        {
            int today = i % 2;
            int yesterday = (i - 1) % 2;
            dp[today].first = std::max(dp[yesterday].first, dp[yesterday].second - prices[i] - fee);
            dp[today].second = std::max(dp[yesterday].second, dp[yesterday].first + prices[i]);
        }

        int lastDay = (prices.size() - 1) % 2;
        return dp[lastDay].second;
    }
};

class Solution2
{
public:
    int maxProfit(std::vector<int> &prices, int fee)
    {
        int result = 0;
        int minPrice = prices[0];
        for (int i = 1; i < prices.size() - 1; ++i)
        {
            if (prices[i] < minPrice)
            {
                minPrice = prices[i];
            }
            else
            {
                // i是极大值点
                if (prices[i] >= prices[i - 1] && prices[i] > prices[i + 1])
                {
                    int profit = prices[i] - minPrice - fee;
                    if (profit > 0)
                    {
                        result += profit;
                        minPrice = prices[i] - fee;
                    }
                }
            }
        }
        if (prices.back() - minPrice - fee > 0)
        {
            result += prices.back() - minPrice - fee;
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
