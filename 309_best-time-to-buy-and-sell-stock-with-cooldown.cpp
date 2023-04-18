#include <iostream>
#include <vector>

class Solution
{
public:
    struct Status
    {
        /** 携带股票状态：
         *  1.昨天就携带了股票
         *  2.昨天是冷冻期，今天买入了股票
         *  3.昨天未持有股票，今天买入了股票  */
        int takeStock{0};

        /** 不持有股票状态
         *  1.昨天就是不持有股票状态
         *  2.昨天是冷却期，今天不买股票 */
        int noStock{0};

        /** 股票卖出状态，昨天持有股票，今天卖出 */
        int sell{0};

        /** 处于冷却期，昨天卖出了股票 */
        int cooldown{0};
    };

    int maxProfit(std::vector<int> &prices)
    {
        if (prices.size() <= 1)
            return 0;

        std::vector<Status> dp(2);
        dp[0].takeStock = -prices[0];

        for (int i = 1; i < prices.size(); ++i)
        {
            dp[i % 2].takeStock = std::max(dp[(i - 1) % 2].takeStock,
                                       std::max(dp[(i - 1) % 2].cooldown - prices[i], dp[(i - 1) % 2].noStock - prices[i]));
            dp[i % 2].noStock = std::max(dp[(i - 1) % 2].noStock, dp[(i - 1) % 2].cooldown);
            dp[i % 2].sell = dp[(i - 1) % 2].takeStock + prices[i];
            dp[i % 2].cooldown = dp[(i - 1) % 2].sell;
        }

        Status &result = dp[(prices.size() - 1) % 2];
        return std::max(result.noStock, std::max(result.sell, result.cooldown));
    }
};

int main()
{
    Solution solution;
    std::vector<int> prices = {1,2,3,0,2};
    std::cout << solution.maxProfit(prices) << std::endl;
    return 0;
}