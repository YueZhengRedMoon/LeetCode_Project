#include <iostream>
#include <vector>
#include <algorithm>

namespace TimeLimit
{
    class Solution
    {
    public:
        long long sellingWood(int m, int n, std::vector<std::vector<int>>& prices)
        {
            // 按w从低到高排序
            std::sort(prices.begin(), prices.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
                return a[1] < b[1];
            });

            // f[i][j]:高为i，宽为j的木块可以得到的最多钱数
            std::vector<std::vector<long long>> f(m + 1, std::vector<long long>(n + 1, 0));
            for (int i = 1; i <= m; ++i)
            {
                for (int j = 1; j <= n; ++j)
                {
                    for (const std::vector<int>& price : prices)
                    {
                        int h = price[0], w = price[1], p = price[2];
                        if (j < w)
                            break;

                        if (i >= h)
                        {
                            f[i][j] = std::max({f[i][j], f[i - h][j] + f[h][j - w] + p, f[i][j - w] + f[i - h][w] + p});
                        }
                    }
                }
            }

            return f[m][n];
        }
    };
}

class Solution
{
public:
    long long sellingWood(int m, int n, std::vector<std::vector<int>>& prices)
    {
        // f[i][j]：切割一块高i宽j的木块，能得到的最多钱数
        std::vector<std::vector<long long>> f(m + 1, std::vector<long long>(n + 1));
        for (const std::vector<int>& p : prices)
        {
            f[p[0]][p[1]] = p[2];
        }

        for (int i = 1; i <= m; ++i)    // 枚举高
        {
            for (int j = 1; j <= n; ++j)    // 枚举宽
            {
                // 枚举竖向切割位置
                for (int k = 1; k <= j / 2; ++k)
                    f[i][j] = std::max(f[i][j], f[i][k] + f[i][j - k]);

                // 枚举横向切割位置
                for (int k = 1; k <= i / 2; ++k)
                    f[i][j] = std::max(f[i][j], f[k][j] + f[i - k][j]);
            }
        }

        return f[m][n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
