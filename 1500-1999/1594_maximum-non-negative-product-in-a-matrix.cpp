#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxProductPath(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        // fMin[i][j]:从grid[0][0]到达grid[i][j]的最小路径乘积
        std::vector<std::vector<long long>> fMin(m, std::vector<long long>(n));
        // fMax[i][j]:从grid[0][0]到达grid[i][j]的最小路径乘积
        std::vector<std::vector<long long>> fMax(m, std::vector<long long>(n));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                long long x = grid[i][j];

                if (i == 0 && j == 0)
                {
                    fMin[0][0] = x;
                    fMax[0][0] = x;
                    continue;
                }

                long long resMin = LLONG_MAX, resMax = LLONG_MIN;

                if (i > 0)
                {
                    resMin = std::min(fMin[i - 1][j] * x, fMax[i - 1][j] * x);
                    resMax = std::max(fMin[i - 1][j] * x, fMax[i - 1][j] * x);
                }
                if (j > 0)
                {
                    resMin = std::min({resMin, fMin[i][j - 1] * x, fMax[i][j - 1] * x});
                    resMax = std::max({resMax, fMin[i][j - 1] * x, fMax[i][j - 1] * x});
                }

                fMin[i][j] = resMin;
                fMax[i][j] = resMax;
            }
        }

        return fMax[m - 1][n - 1] < 0 ? -1 : fMax[m - 1][n - 1] % 1'000'000'007;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}