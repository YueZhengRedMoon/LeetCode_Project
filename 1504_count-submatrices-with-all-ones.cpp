#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int numSubmat(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        int sum = 0;

        for (int i = 0; i < m; ++i)
        {
            dp[i][0] = matrix[i][0];
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    int minLen = std::numeric_limits<int>::max();

                    if (j != 0)
                        dp[i][j] = dp[i][j - 1] + 1;    // 有多少连续1

                    for (int k = i; k >= 0 && dp[k][j] > 0; --k)
                    {
                        minLen = std::min(minLen, dp[k][j]);
                        sum += minLen;
                    }
                }
            }
        }

        return sum;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}