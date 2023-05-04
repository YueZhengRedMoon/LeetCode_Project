#include <iostream>
#include <vector>
#include <limits>
#include "debug.h"

class Solution
{
public:
    int minPathSum(std::vector<std::vector<int>> &grid)
    {
        int row = grid.size();
        int col = grid[0].size();

        // dp[i][j]:从grid[0][0]到grid[i][j]的最小路径和
        std::vector<std::vector<int>> dp(row, std::vector<int>(col));

        // 初始化
        dp[0][0] = grid[0][0];
        for (int i = 1; i < row; ++i)
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int j = 1; j < col; ++j)
            dp[0][j] = dp[0][j - 1] + grid[0][j];

        for (int i = 1; i < row; ++i)
        {
            for (int j = 1; j < col; ++j)
            {
                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        return dp[row - 1][col - 1];
    }
};

class Solution2
{
public:
    int minPathSum(std::vector<std::vector<int>> &grid)
    {
        int row = grid.size();
        int col = grid[0].size();

        std::vector<int> dp(col, std::numeric_limits<int>::max());
        dp[0] = 0;

        for (int i = 0; i < row; ++i)
        {
            dp[0] += grid[i][0];
            for (int j = 1; j < col; ++j)
            {
                dp[j] = std::min(dp[j - 1], dp[j]) + grid[i][j];
            }
        }

        return dp[col - 1];
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{1,2,3},{4,5,6}};
    int result = solution.minPathSum(grid);
    std::cout << result << std::endl;
    return 0;
}