#include <iostream>
#include <vector>

class Solution
{
public:
    int maxProfit(std::vector<int> &prices)
    {
//        for (int &price : prices)
//        {
//            ++price;    // 所有股票价格+1,避免股票价格为0的特殊情况
//        }

        // 在股票价格到达极小值时买入，在股票价格到达极大值时卖出
        int profit = 0; // 总利润
        int buyingPrice = 0;    // 买入股票时的价格
        bool hold = false;      // 当前持有股票
        // prices[i] - prices[i - 1]，初始化为-1，这样如果princes[1]-prices[0]大于0，就说明第一天(i=1)是极小值点
        int last = -1;
        for (int i = 0; i < prices.size() - 1; ++i)
        {
            int delta = prices[i + 1] - prices[i];
            // 到达了极值点，
            if (delta != 0 && last * delta < 0)
            {
                // 持有股票
                if (hold)
                {
                    // 卖出股票
                    profit += prices[i] - buyingPrice;
                    buyingPrice = 0;
                    hold = false;
                }
                // 没有持有股票
                else
                {
                    // 买入股票
                    buyingPrice = prices[i];
                    hold = true;
                }
                last = delta;
            }
        }
        // 到最后一天时，只要持有股票，就卖出
        if (hold)
        {
            profit += prices[prices.size() - 1] - buyingPrice;
        }
        return profit;
    }
};

class Solution2
{
public:
    int maxProfit(std::vector<int> &prices)
    {
        int result = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            result += std::max(prices[i] - prices[i - 1], 0);
        }
        return result;
    }
};


int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
