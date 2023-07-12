#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minFallingPathSum(std::vector<std::vector<int>> &matrix)
    {
        int n = matrix.size();
        if (n == 1)
        {
            return matrix[0][0];
        }

        std::vector<std::vector<int>> dp(2, std::vector<int>(n, 0));
        std::copy(matrix[0].begin(), matrix[0].end(), dp[0].begin());

        for (int i = 1; i < n; ++i)
        {
            int cur = i % 2, last = (i - 1) % 2;
            dp[cur][0] = std::min(dp[last][0], dp[last][1]) + matrix[i][0];
            for (int j = 1; j < n - 1; ++j)
            {
                dp[cur][j] = std::min({dp[last][j - 1], dp[last][j], dp[last][j + 1]}) + matrix[i][j];
            }
            dp[cur][n - 1] = std::min(dp[last][n - 2], dp[last][n - 1]) + matrix[i][n - 1];
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