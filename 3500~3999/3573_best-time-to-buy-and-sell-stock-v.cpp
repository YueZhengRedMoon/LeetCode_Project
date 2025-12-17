#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

class Solution
{
public:
    long long maximumProfit(std::vector<int>& prices, int k)
    {
        int n = prices.size();
        // f[i][j][0]:在prices[0, i)中完成j笔交易，第i天结束时未持有股票时的最大利润
        // f[i][j][1]:在prices[0, i)中完成j笔交易，第i天结束时持有股票时的最大利润
        // f[i][j][2]:在prices[0, i)中完成j笔交易，第i天结束时处于做空中的最大利润
        std::vector<std::vector<std::array<long long, 3>>> f(n + 1, std::vector<std::array<long long, 3>>(k + 2,  {LLONG_MIN / 2, LLONG_MIN / 2, LLONG_MIN / 2}));
        for (int j = 1; j <= k + 1; ++j)
        {
            f[0][j][0] = 0;
        }
        for (int i = 0; i < n; ++i)
        {
            int p = prices[i];
            for (int j = 1; j <= k + 1; ++j)
            {
                f[i + 1][j][0] = std::max({f[i][j][0], f[i][j][1] + p, f[i][j][2] - p});
                f[i + 1][j][1] = std::max(f[i][j][1], f[i][j - 1][0] - p);
                f[i + 1][j][2] = std::max(f[i][j][2], f[i][j - 1][0] + p);
            }
        }
        return f[n][k + 1][0];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}