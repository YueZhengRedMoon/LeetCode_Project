#include <iostream>
#include <vector>

class Solution
{
public:
    long long maxProfit(std::vector<int>& prices, std::vector<int>& strategy, int k)
    {
        int n = prices.size();
        // profitPrefix[i]=prices[0]*strategy[0]+prices[1]*strategy[1]+...+prices[i-1]*strategy[i-1]
        std::vector<long long> profitPrefix(n + 1, 0);
        // pricesPrefix[i]=sum(prices[0, i))
        std::vector<long long> pricesPrefix(n + 1, 0);
        for (int i = 0; i < n; ++i)
        {
            profitPrefix[i + 1] = profitPrefix[i] + prices[i] * strategy[i];
            pricesPrefix[i + 1] = pricesPrefix[i] + prices[i];
        }

        long long ans = profitPrefix[n];
        for (int l = 0, r = k, m = (l + r) / 2; r <= n; ++l, ++r, ++m)    // 滑动窗口[l, r)
        {
            long long profit = profitPrefix[l]; // [0, l)的利润
            // [l, m)的利润变为0
            profit += pricesPrefix[r] - pricesPrefix[m];    // [m, r)的利润
            profit += profitPrefix[n] - profitPrefix[r];    // [r, n)的利润

            if (profit > ans)
                ans = profit;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}