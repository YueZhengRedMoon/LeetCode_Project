#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minFallingPathSum(std::vector<std::vector<int>> &grid)
    {
        const int inf = 0x3f3f3f3f;
        int n = grid.size();
        std::vector<std::vector<int>> dp = {grid[0], std::vector<int>(n)};
        for (int i = 1; i < n; ++i)
        {
            int cur = i % 2, last = (i - 1) % 2;
            int min1 = inf, min2 = inf, minIndex1 = -1;
            for (int j = 0; j < n; ++j)
            {
                if (dp[last][j] < min1)
                {
                    min2 = min1;
                    min1 = dp[last][j];
                    minIndex1 = j;
                }
                else if (dp[last][j] < min2)
                {
                    min2 = dp[last][j];
                }
            }
            for (int j = 0; j < n; ++j)
            {
                if (j != minIndex1)
                {
                    dp[cur][j] = min1 + grid[i][j];
                }
                else
                {
                    dp[cur][j] = min2 + grid[i][j];
                }
            }
        }

        int end = (n - 1) % 2;
        return *std::min_element(dp[end].begin(), dp[end].end());
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}