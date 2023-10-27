#include <iostream>
#include <vector>

class Solution
{
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size();    // 纵向维度
        int n = obstacleGrid[0].size(); // 横向维度

        // dp[i][j]:从dp[0][0]到dp[i][j]有几种走法
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        // 初始化
        dp[0][0] = obstacleGrid[0][0] ? 0 : 1;
        for (int i = 1; i < m; ++i)
        {
            dp[i][0] = obstacleGrid[i][0] == 1 ? 0 : dp[i - 1][0];
        }
        for (int j = 1; j < n; ++j)
        {
            dp[0][j] = obstacleGrid[0][j] == 1 ? 0 : dp[0][j - 1];
        }

        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                if (obstacleGrid[i][j])
                {
                    dp[i][j] = 0;
                }
                else
                {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};

class Solution2
{
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> &obstacleGrid)
    {
        int m = obstacleGrid.size();    // 纵向维度
        int n = obstacleGrid[0].size(); // 横向维度

        // dp[i][j]:从dp[0][0]到dp[i][j]有几种走法
        std::vector<int> dp(n, 0);

        // 初始化
        dp[0] = obstacleGrid[0][0] ? 0 : 1;
        for (int j = 1; j < n; ++j)
        {
            dp[j] = obstacleGrid[0][j] ? 0 : dp[j - 1];
        }

        for (int i = 1; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (obstacleGrid[i][j])
                {
                    dp[j] = 0;
                }
                else
                {
                    if (j >= 1)
                    {
                        dp[j] += dp[j - 1];
                    }
                }
            }
        }

        return dp[n - 1];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
