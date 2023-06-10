#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Solution
{
public:
    int minCostII(std::vector<std::vector<int>> &costs)
    {
        const int inf = std::numeric_limits<int>::max();
        int n = costs.size(), k = costs[0].size();
        // dp[i][j]:将i号房子染成j色的最小成本
        std::vector<std::vector<int>> dp(2, std::vector<int>(k));
        // 将房子染色需要的最小成本以及最后一个房子被染成的颜色
        int min1 = inf, color1 = 0;
        // 将房子染色需要的第二小成本
        int min2 = inf;
        for (int i = 0; i < k; ++i)
        {
            dp[0][i] = costs[0][i];
            if (costs[0][i] < min1)
            {
                min2 = min1;
                min1 = costs[0][i];
                color1 = i;
            }
            else if (costs[0][i] < min2)
            {
                min2 = costs[0][i];
            }
        }

        for (int i = 1; i < n; ++i)
        {
            int cur = i % 2;
            int lastMin1 = min1, lastColor1 = color1;
            int lastMin2 = min2;
            min1 = min2 = inf;
            for (int j = 0; j < k; ++j)
            {
                if (j != lastColor1)
                {
                    dp[cur][j] = lastMin1 + costs[i][j];
                }
                else
                {
                    dp[cur][j] = lastMin2 + costs[i][j];
                }
                if (dp[cur][j] < min1)
                {
                    min2 = min1;
                    min1 = dp[cur][j];
                    color1 = j;
                }
                else if (dp[cur][j] < min2)
                {
                    min2 = dp[cur][j];
                }
            }
        }

        return min1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
