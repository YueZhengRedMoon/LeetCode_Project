#include <iostream>
#include <vector>

class Solution
{
public:
    int numMagicSquaresInside(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        auto check = [&](int i, int j) -> bool {
            int set = 0;
            for (int x = i; x < i + 3; ++x)
            {
                for (int y = j; y < j + 3; ++y)
                {
                    if (grid[x][y] <= 0 || grid[x][y] > 9)
                        return false;

                    if (set & (1 << grid[x][y]))
                    {
                        return false;
                    }
                    else
                    {
                        set |= (1 << grid[x][y]);
                    }
                }
            }

            int sum = grid[i][j] + grid[i][j + 1] + grid[i][j + 2];

            // 检查行是否相等
            for (int k = 1; k < 3; ++k)
            {
                if (grid[i + k][j] + grid[i + k][j + 1] + grid[i + k][j + 2] != sum)
                    return false;
            }

            // 检查列是否相等
            for (int k = 0; k < 3; ++k)
            {
                if (grid[i][j + k] + grid[i + 1][j + k] + grid[i + 2][j + k] != sum)
                    return false;
            }

            // 检查对角线是否相等
            if (grid[i][j] + grid[i + 1][j + 1] + grid[i + 2][j + 2] != sum ||
                grid[i][j + 2] + grid[i + 1][j + 1] + grid[i + 2][j] != sum)
                return false;

            return true;
        };

        int ans = 0;
        for (int i = 0; i <= m - 3; ++i)
        {
            for (int j = 0; j <= n - 3; ++j)
            {
                if (check(i, j))
                    ++ans;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int numMagicSquaresInside(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();

        // 检查以grid[i][j]为左上角的3*3矩阵是否是幻方（每行每列和对角线元素和都为15）
        //  - 在满足3*3矩阵中所有元素都是1~9中的数字且每个数字只出现一次的情况下：
        //  - 1.幻方中心一定是5
        //  - 2.如果第1行/列，第2行/列的和为15，则第3行/列的和一定为15
        //  - 3.在满足上述2个条件的情况下，对角线元素之和一定为15
        auto check = [&](int i, int j) -> bool {
            if (grid[i + 1][j + 1] != 5)
                return false;

            int set = 0;
            for (int x = i; x < i + 3; ++x)
            {
                for (int y = j; y < j + 3; ++y)
                {
                    if (grid[x][y] <= 0 || grid[x][y] > 9)
                        return false;

                    if (set & (1 << grid[x][y]))
                    {
                        return false;
                    }
                    else
                    {
                        set |= (1 << grid[x][y]);
                    }
                }
            }

            // 检查行是否相等
            if (grid[i][j] + grid[i][j + 1] + grid[i][j + 2] != 15 ||
                grid[i + 1][j] + grid[i + 1][j + 1] + grid[i + 1][j + 2] != 15)
            {
                return false;
            }

            // 检查列是否相等
            if (grid[i][j] + grid[i + 1][j] + grid[i + 2][j] != 15 ||
                grid[i][j + 1] + grid[i + 1][j + 1] + grid[i + 2][j + 1] != 15)
            {
                return false;
            }

            // 无需检查对角线是否相等

            return true;
        };

        int ans = 0;
        for (int i = 0; i <= m - 3; ++i)
        {
            for (int j = 0; j <= n - 3; ++j)
            {
                if (check(i, j))
                    ++ans;
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