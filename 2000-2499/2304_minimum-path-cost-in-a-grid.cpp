#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    int minPathCost(std::vector<std::vector<int>> &grid, std::vector<std::vector<int>> &moveCost)
    {
        const int inf = std::numeric_limits<int>::max();
        int m = grid.size(), n = grid[0].size();
        // dp[i][j]:从第一行到达grid[i][j]的最小代价
        std::vector<std::vector<int>> dp(2, std::vector<int>(n, 0));

        for (int i = 1; i < m; ++i)
        {
            int last = (i - 1) % 2, cur = i % 2;
            for (int j = 0; j < n; ++j)
            {
                dp[cur][j] = inf;
                for (int k = 0; k < n; ++k)
                {
                    int fromValue = grid[i - 1][k];
                    dp[cur][j] = std::min(dp[cur][j], dp[last][k] + fromValue + moveCost[fromValue][j]);
                }
            }

            debug::printVector(dp[cur]);
        }

        int lastRow = (m - 1) % 2;
        for (int j = 0; j < n; ++j)
        {
            dp[lastRow][j] += grid[m - 1][j];
        }
        return *std::min_element(dp[lastRow].begin(), dp[lastRow].end());
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{5,3},{4,0},{2,1}};
    std::vector<std::vector<int>> moveCost = {{9,8},{1,5},{10,12},{18,6},{2,4},{14,3}};
    int ans = solution.minPathCost(grid, moveCost);
    logObj(ans);
    return 0;
}
