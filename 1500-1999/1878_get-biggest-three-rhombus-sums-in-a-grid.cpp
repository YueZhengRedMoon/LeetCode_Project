#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> getBiggestThree(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        // diagSum[i+1][j+1] 表示从矩阵最上边或最左边出发，向右下↘到 (i,j)，这条线段的元素和
        // 从 (x,y) 开始，向右下↘连续 k 个数的和为 diagSum[x+k][y+k]−diagSum[x][y]。
        std::vector<std::vector<int>> diagSum(m + 1, std::vector<int>(n + 1));
        // antiSum[i+1][j] 表示从矩阵最上边或最右边出发，向左下↙到 (i,j)，这条线段的元素和
        // 从 (x,y) 开始，向左下↙连续 k 个数的和为 antiSum[x+k][y+1−k]−antiSum[x][y+1]
        std::vector<std::vector<int>> antiSum(m + 1, std::vector<int>(n + 1));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int v = grid[i][j];
                diagSum[i + 1][j + 1] = diagSum[i][j] + v;
                antiSum[i + 1][j] = antiSum[i][j + 1] + v;
            }
        }

        // 从 (x,y) 开始，向 ↘，连续 k 个数的和
        auto queryDiagonal = [&](int x, int y, int k) -> int {
            return diagSum[x + k][y + k] - diagSum[x][y];
        };

        // 从 (x,y) 开始，向 ↙，连续 k 个数的和
        auto queryAntiDiagonal = [&](int x, int y, int k) -> int {
            return antiSum[x + k][y + 1 - k] - antiSum[x][y + 1];
        };

        int x = 0, y = 0, z = 0; // 最大，次大，第三大
        auto update = [&](int v) -> void {
            if (v > x)
            {
                z = y;
                y = x;
                x = v;
            }
            else if (v < x && v > y)
            {
                z = y;
                y = v;
            }
            else if (v < y && v > z)
            {
                z = v;
            }
        };

        // 枚举菱形正中心 (i,j)
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                update(grid[i][j]); // 一个数也算菱形

                // 枚举菱形顶点到正中心的距离 k，注意菱形顶点不能出界
                // i-k >= 0 且 i+k <= m-1，所以 k <= min(i, m-1-i)，对于 j 同理
                int maxK = std::min({i, m - 1 - i, j, n - 1 - j});
                for (int k = 1; k <= maxK; ++k)
                {
                    int a = queryDiagonal(i - k, j, k); // 菱形右上的边
                    int b = queryDiagonal(i, j - k, k); // 菱形左下的边
                    int c = queryAntiDiagonal(i - k + 1, j - 1, k - 1); // 菱形左上的边
                    int d = queryAntiDiagonal(i, j + k, k + 1); // 菱形右下的边
                    update(a + b + c + d);
                }
            }
        }

        std::vector<int> ans = {x, y, z};
        while (ans.back() == 0) // 不同的和少于三个
        {
            ans.pop_back();
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}