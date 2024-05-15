#include <iostream>
#include <vector>
#include <numeric>
#include "debug.h"

class Solution
{
public:
    int profitableSchemes(int n, int minProfit, std::vector<int>& group, std::vector<int>& profit)
    {
        const int MOD = 1'000'000'007;
        int m = profit.size();  // 任务数
        int maxProfit = std::accumulate(profit.begin(), profit.end(), 0);
        int ans = 0;

        // f[i][j]:产生利润为i，共j名员工参与的计划数
        std::vector<std::vector<int>> f(maxProfit + 1, std::vector<int>(n + 1, 0));
        f[0][0] = 1;
        for (int k = 0; k < m; ++k)
        {
            for (int i = maxProfit; i >= profit[k]; --i)
            {
                for (int j = n; j >= group[k]; --j)
                {
                    f[i][j] = (f[i][j] + f[i - profit[k]][j - group[k]]) % MOD;
                }
            }
        }

        for (int i = minProfit; i <= maxProfit; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                ans = (ans + f[i][j]) % MOD;
            }
        }

        debug::printVector2D(f);

        return ans;
    }
};

int main()
{
    Solution solution;
    int n = 5, minProfit = 3;
    std::vector<int> group = {2, 2}, profit = {2, 3};
    int ans = solution.profitableSchemes(n, minProfit, group, profit);
    logObj(ans);
    return 0;
}
