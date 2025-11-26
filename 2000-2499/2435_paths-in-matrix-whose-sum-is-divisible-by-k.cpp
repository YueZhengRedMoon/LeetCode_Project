#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfPaths(std::vector<std::vector<int>>& grid, int k)
    {
        constexpr int MOD = 1'000'000'007;
        int m = grid.size(), n = grid[0].size();

        // f[x][y][i]:从[0,0]到达[x,y]的路径和 mod k == i的路径数目
        std::vector<std::vector<std::vector<int>>> f(m, std::vector<std::vector<int>>(n, std::vector<int>(k, 0)));
        f[0][0][grid[0][0] % k] = 1;
        for (int x = 0; x < m; ++x)
        {
            for (int y = 0; y < n; ++y)
            {
                int cur = grid[x][y];   // 当前格子的值

                for (int i = 0; i < k; ++i)
                {
                    // 从左边的格子(x,y-1)到达当前格子
                    if (y > 0)
                    {
                        f[x][y][i] = f[x][y - 1][(i - cur + 100 * k) % k];
                    }

                    // 从上边的格子(x-1,y)到达当前格子
                    if (x > 0)
                    {
                        f[x][y][i] = (f[x][y][i] + f[x - 1][y][(i - cur + 100 * k) % k]) % MOD;
                    }
                }
            }
        }
        return f[m - 1][n - 1][0];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}