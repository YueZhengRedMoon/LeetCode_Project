#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug.h"

class Solution
{
public:
    int countSquares(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        int ans = 0;
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (matrix[i - 1][j - 1] == 1)
                {
                    dp[i][j] = std::min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                    ans += dp[i][j];
                }
            }
        }

        debug::printVector2D(dp);

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> matrix = {{0,1,1,1},{1,1,1,1},{0,1,1,1}};
    int ans = solution.countSquares(matrix);
    std::cout << ans << std::endl;
    return 0;
}