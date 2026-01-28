#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

class Solution
{
public:
    using Tuple3 = std::tuple<int, int, int>;

    int minCost(std::vector<std::vector<int>>& grid, int k)
    {
        int m = grid.size(), n = grid[0].size(), mn = m * n;

        if (k > 0 && grid[0][0] >= grid[m - 1][n - 1])
            return 0;

        std::vector<Tuple3> cells;
        cells.reserve(mn);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cells.emplace_back(grid[i][j], i, j);
            }
        }
        std::sort(cells.begin(), cells.end());
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        auto lowerBound = [&](int i, int j) -> int {
            if (memo[i][j] != -1)
                return memo[i][j];

            int left = 0, right = mn, res = -1, target = grid[i][j];
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (std::get<0>(cells[mid]) >= target)
                {
                    res = mid;
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }
            return memo[i][j] = res;
        };

        // f[i][j][t]:从grid[0][0]经过t次传送到达grid[i][j]的最小成本;=INF表示无法抵达
        const int INF = INT_MAX;
        int ans = INF;
        std::vector<std::vector<std::vector<int>>> f(m, std::vector<std::vector<int>>(n, std::vector<int>(k + 1, INF)));
        std::vector<int> minF(mn, INF);
        f[0][0][0] = 0;
        for (int t = 0; t <= k; ++t)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    // 从上边的格子到达当前格子
                    if (i > 0)
                    {
                        f[i][j][t] = f[i - 1][j][t] + grid[i][j];
                    }

                    // 从左边的格子到达当前格子
                    if (j > 0)
                    {
                        f[i][j][t] = std::min(f[i][j][t], f[i][j - 1][t] + grid[i][j]);
                    }

                    // 从比当前格子grid[i][j]小的格子grid[x][y]传送来
                    if (t > 0)
                    {
                        int begin = lowerBound(i, j);
                        f[i][j][t] = std::min(f[i][j][t], minF[begin]);
                    }
                }
            }

            minF[mn - 1] = f[std::get<1>(cells[mn - 1])][std::get<2>(cells[mn - 1])][t];
            for (int i = mn - 2; i >= 0; --i)
            {
                minF[i] = std::min(f[std::get<1>(cells[i])][std::get<2>(cells[i])][t], minF[i + 1]);
            }

            ans = std::min(ans, f[m - 1][n - 1][t]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}