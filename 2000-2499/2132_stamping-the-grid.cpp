#include <iostream>
#include <vector>

class Solution
{
public:
    bool possibleToStamp(std::vector<std::vector<int>> &grid, int stampHeight, int stampWidth)
    {
        int m = grid.size(), n = grid[0].size();

        // 1.计算grid的二维前缀和
        std::vector<std::vector<int>> s(m + 1, std::vector<int>(n + 1));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + grid[i][j];
            }
        }

        // 2.计算二维差分
        // 为方便第3步的计算，在d数组的最上面和最左边各加了一行（列），所以下标要+1
        std::vector<std::vector<int>> d(m + 2, std::vector<int>(n + 2));
        for (int i2 = stampHeight; i2 <= m; ++i2)
        {
            for (int j2 = stampWidth; j2 <= n; ++j2)
            {
                int i1 = i2 - stampHeight + 1, j1 = j2 - stampWidth + 1;
                if (s[i2][j2] - s[i2][j1 - 1] - s[i1 - 1][j2] + s[i1 - 1][j1 - 1] == 0)
                {
                    ++d[i1][j1];
                    --d[i1][j2 + 1];
                    --d[i2 + 1][j1];
                    ++d[i2 + 1][j2 + 1];
                }
            }
        }

        // 3. 还原二维差分矩阵对应的计数矩阵（原地计算）
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                d[i + 1][j + 1] += d[i + 1][j] + d[i][j + 1] - d[i][j];
                if (grid[i][j] == 0 && d[i + 1][j + 1] == 0)
                    return false;
            }
        }

        return true;
    }
};

namespace Error
{
    class Solution
    {
    public:
        bool possibleToStamp(std::vector<std::vector<int>> &grid, int stampHeight, int stampWidth)
        {
            int m = grid.size(), n = grid[0].size();
            for (int i = 0; i < m; ++i)
            {
                int lastOccupied = -1, blank;
                for (int j = 0; j < n; ++j)
                {
                    if (grid[i][j])
                    {
                        blank = j - lastOccupied - 1;
                        if (blank > 0 && blank < stampWidth)
                            return false;
                        lastOccupied = j;
                    }
                }
                blank = n - lastOccupied - 1;
                if (blank > 0 && blank < stampWidth)
                    return false;
            }

            for (int j = 0; j < n; ++j)
            {
                int lastOccupied = -1, blank;
                for (int i = 0; i < m; ++i)
                {
                    if (grid[i][j])
                    {
                        blank = i - lastOccupied - 1;
                        if (blank > 0 && blank < stampHeight)
                            return false;
                        lastOccupied = i;
                    }
                }
                blank = m - lastOccupied - 1;
                if (blank > 0 && blank < stampHeight)
                    return false;
            }

            return true;
        }
    };
}

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}};
    int stampHeight = 9;
    int stampWidth = 4;
    bool ans = solution.possibleToStamp(grid, stampHeight, stampWidth);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
