#include <iostream>
#include <vector>
#include <limits>

/** 错误，例如prices = {2, 4, 1}，正确答案应该是2，按照下面的方法计算出的值是0 */
class Solution
{
public:
    int maxProfit(std::vector<int> &prices)
    {
        int minPrice = prices[0];
        int minIndex = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            if (prices[i] < minPrice)
            {
                minPrice = prices[i];
                minIndex = i;
            }
        }

        int maxPrice = -1;
        for (int i = minIndex + 1; i < prices.size(); ++i)
        {
            if (prices[i] > maxPrice)
            {
                maxPrice = prices[i];
            }
        }

        return std::max(maxPrice - minPrice, 0);
    }
};

class Solution2
{
public:
    int maxProfit(std::vector<int> &prices)
    {
        // minPrices[i]:prices[0:i]中的最小值
        std::vector<int> minPrices(prices.size(), 0);
        minPrices[0] = prices[0];
        for (int i = 1; i < prices.size(); ++i)
        {
            minPrices[i] = std::min(minPrices[i - 1], prices[i]);
        }

        // maxPrices[i]:prices[i+1:n-1]中的最大值
        std::vector<int> maxPrices(prices.size(), 0);
        maxPrices[prices.size() - 1] = -1;
        for (int i = prices.size() - 2; i >= 0; --i)
        {
            maxPrices[i] = std::max(maxPrices[i + 1], prices[i + 1]);
        }

        int result = 0;
        for (int i = 0; i < prices.size(); ++i)
        {
            result = std::max(result, maxPrices[i] - minPrices[i]);
        }

        return result;
    }
};

class Solution3
{
public:
    int maxProfit(std::vector<int> &prices)
    {
        int lowest = std::numeric_limits<int>::max();
        int result = 0;
        for (int i = 0; i < prices.size(); ++i)
        {
            lowest = std::min(lowest, prices[i]);
            result = std::max(result, prices[i] - lowest);
        }
        return result;
    }
};

class Solution4
{
public:
    int maxProfit(std::vector<int> &prices)
    {
        // dp[i][0]:第i天不持有股票的最大利润
        // dp[i][1]:第i天持有股票的最大利润
        std::vector<std::vector<int>> dp(2, std::vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < prices.size(); ++i)
        {
            dp[i % 2][0] = std::max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] + prices[i]);
            dp[i % 2][1] = std::max(dp[(i - 1) % 2][1], -prices[i]);
         }

        return dp[(prices.size() - 1) % 2][0];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
