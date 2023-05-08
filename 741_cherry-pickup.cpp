#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int cherryPickup(std::vector<std::vector<int>> &grid)
    {
        // 从(N-1, N-1)返回(0,0)的路径可以等价成从(0, 0)到(N-1, N-1)的路径
        // 问题可以等价成两个人从(0, 0)出发，向下或向右走到(N-1, N-1)时，摘到的樱桃个数之和的最大值
       int n = grid.size();

       // dp[k][x1][x2]表示两个人(设为A和B)分别从(x1, k-x1)和(x2,k-x2)同时出发，到达(N-1, N-1)摘到的樱桃个数之和的最大值
       // 如果x1 == x2，则表示两人走到同一个格子
       // 如果(x, y)是荆棘，则dp[k][x][y] = -inf
       std::vector<std::vector<std::vector<int>>> dp(n * 2 - 1,
                                                     std::vector<std::vector<int>>(n,
                                                             std::vector<int>(n,
                                                                              std::numeric_limits<int>::min())));
       dp[0][0][0] = grid[0][0];
       for (int k = 1; k < n * 2 - 1; ++k)
       {
           for (int x1 = std::max(k - n + 1, 0); x1 <= std::min(k, n - 1); ++x1)
           {
               int y1 = k - x1;
               if (grid[x1][y1] == -1)
               {
                   continue;
               }
               for (int x2 = x1; x2 <= std::min(k, n - 1); ++x2)
               {
                   int y2 = k - x2;
                   if (grid[x2][y2] == -1)
                   {
                       continue;
                   }
                   // 都往右
                   int res = dp[k - 1][x1][x2];
                   // 往下，往右
                   if (x1)
                       res = std::max(res, dp[k - 1][x1 - 1][x2]);
                   // 往右，往下
                   if (x2)
                       res = std::max(res, dp[k - 1][x1][x2 - 1]);
                   // 都往下
                   if (x1 && x2)
                   {
                       res = std::max(res, dp[k - 1][x1 - 1][x2 - 1]);
                   }

                   res += grid[x1][y1];
                   if (x2 != x1)
                   {
                       res += grid[x2][y2];
                   }
                   dp[k][x1][x2] = res;
               }
           }
       }

       return std::max(dp.back().back().back(), 0);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
