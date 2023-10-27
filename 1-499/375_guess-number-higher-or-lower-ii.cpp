#include <iostream>
#include <vector>
#include <limits>
#include "../debug.h"

class Solution
{
public:
    int getMoneyAmount(int n)
    {
        const int inf = std::numeric_limits<int>::max();
        // dp[i][j]:猜中范围在[i, j]内的数最少需要的现金
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, inf));

        for (int i = n; i >= 0; --i)
        {
            for (int j = i; j <= n; ++j)
            {
                if (i == j)
                {
                    dp[i][j] = 0;
                }
                else if (i + 1 == j)
                {
                    dp[i][j] = i;
                }
                else
                {
                    dp[i][j] = std::min(i + dp[i + 1][j], dp[i][j - 1] + j);
                    for (int k = i + 1; k < j ; ++k)
                    {
                        dp[i][j] = std::min(dp[i][j], k + std::max(dp[i][k - 1], dp[k + 1][j]));
                    }
                }
            }
        }
        debug::printVector2D(dp, inf, '\t');

        return dp[0][n];
    }
};

int main()
{
    Solution solution;
    int n = 10;
    int ans = solution.getMoneyAmount(n);
    std::cout << ans << std::endl;
    return 0;
}
