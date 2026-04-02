#include <iostream>
#include <vector>

class Solution
{
public:
    int maximumAmount(std::vector<std::vector<int>>& coins)
    {
        int m = coins.size(), n = coins[0].size();
        // f[i][j][k]:从(0,0)到达(i,j)，最多感化k个单元格的强盗，可以取得的最大金币数
        std::vector<std::vector<std::vector<int>>> f(m, std::vector<std::vector<int>>(n, std::vector<int>(3, INT_MIN)));
        f[0][0][0] = coins[0][0];
        f[0][0][1] = f[0][0][2] = std::max(0, coins[0][0]);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    if (i > 0)
                    {
                        f[i][j][k] = f[i - 1][j][k] + coins[i][j];  // 不感化强盗
                        if (coins[i][j] < 0 && k > 0)   // 感化强盗
                        {
                            f[i][j][k] = std::max(f[i][j][k], f[i - 1][j][k - 1]);
                        }
                    }

                    if (j > 0)
                    {
                        f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][k] + coins[i][j]);    // 不感化强盗
                        if (coins[i][j] < 0 && k > 0)   // 感化强盗
                        {
                            f[i][j][k] = std::max(f[i][j][k], f[i][j - 1][k - 1]);
                        }
                    }
                }
            }
        }
        return f[m - 1][n - 1][2];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}