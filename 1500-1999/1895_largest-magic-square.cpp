#include <iostream>
#include <vector>

class Solution
{
public:
    int largestMagicSquare(std::vector<std::vector<int>>& grid)
    {
        int ans = 1, m = grid.size(), n = grid[0].size();

        // 计算左上角为grid[i][j], 边长为k的正方形是否是幻方
        auto check = [&](int i, int j, int k) -> bool {
            int sum = 0, s;
            for (int y = j; y < j + k; ++y)
                sum += grid[i][y];

            // 检查行
            for (int x = i + 1; x < i + k; ++x)
            {
                s = 0;
                for (int y = j; y < j + k; ++y)
                    s += grid[x][y];

                if (s != sum)
                    return false;
            }

            // 检查列
            for (int y = j; y < j + k; ++y)
            {
                s = 0;
                for (int x = i; x < i + k; ++x)
                    s += grid[x][y];

                if (s != sum)
                    return false;
            }

            // 检查主对角线
            s = 0;
            for (int x = i, y = j; x < i + k; ++x, ++y)
                s += grid[x][y];
            if (s != sum)
                return false;

            // 检查副对角线
            s = 0;
            for (int x = i, y = j + k - 1; x < i + k; ++x, --y)
                s += grid[x][y];
            if (s != sum)
                return false;

            return true;
        };

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int k = ans + 1; i + k <= m && j + k <= n; ++k)
                {
                    if (check(i, j, k))
                    {
                        ans = k;
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}