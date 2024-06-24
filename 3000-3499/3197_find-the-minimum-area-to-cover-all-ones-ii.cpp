#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int minimumSum(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        int ans = m * n, s1, s2, s3;

        // 将整个矩形先水平切一刀分成上下两块
        for (int i = 0; i < m - 1; ++i) // 枚举水平切的位置，将grid分为grid[0,i]和grid[i+1, n)上下两块
        {
            int upS = minimumSum(grid, 0, 0, i, n - 1);             // 上半块grid[0,i]包含所有1的最小矩形面积
            if (upS == inf)
                continue;   // 上半块不包含1，跳过

            int downS = minimumSum(grid, i + 1, 0, m - 1, n - 1);   // 下半块grid[i+1,m)包含所有1的最小矩形面积
            if (downS == inf)
                break;  // 下半块不包含1，跳出

            s1 = upS;
            // 在下半块再水平切一刀，枚举水平切第二刀的位置，将grid分成上中下三块
            for (int i2 = i + 1; i2 < m - 1; ++i2)
            {
                s2 = minimumSum(grid, i + 1, 0, i2, n - 1);
                s3 = minimumSum(grid, i2 + 1, 0, m - 1, n - 1);
                ans = std::min(ans, s1 + s2 + s3);
            }

            // 垂直切下半块矩形, 枚举垂直切的位置，将下半块矩形g分为g[0,j]和g[j+1,n)左右两块
            for (int j = 0; j < n - 1; ++j)
            {
                s2 = minimumSum(grid, i + 1, 0, m - 1, j);
                s3 = minimumSum(grid, i + 1, j + 1, m - 1, n - 1);
                ans = std::min(ans, s1 + s2 + s3);
            }
            // 垂直切上半块矩形，枚举垂直切的位置，将上半块矩形g分为g[0,j]和g[j+1,n)左右两块
            s1 = downS;
            for (int j = 0; j < n - 1; ++j)
            {
                s2 = minimumSum(grid, 0, 0, i, j);
                s3 = minimumSum(grid, 0, j + 1, i, n - 1);
                ans = std::min(ans, s1 + s2 + s3);
            }
        }

        // 将整个矩形先垂直切一刀，分成左右两块
        for (int j = 0; j < n - 1; ++j)
        {
            int leftS = minimumSum(grid, 0, 0, m - 1, j);
            if (leftS == inf)
                continue;   // 左半块不包含1，跳过

            int rightS = minimumSum(grid, 0, j + 1, m - 1, n - 1);
            if (rightS == inf)
                break;  // 右半块不包含1，跳出

            s1 = leftS;
            // 在右半块再垂直切一刀，分成左中右三块
            for (int j2 = j + 1; j2 < n - 1; ++j2)
            {
                s2 = minimumSum(grid, 0, j + 1, m - 1, j2);
                s3 = minimumSum(grid, 0, j2 + 1, m - 1, n - 1);
                ans = std::min(ans, s1 + s2 + s3);
            }

            // 水平切右半块，枚举水平切的位置
            for (int i = 0; i < m - 1; ++i)
            {
                s2 = minimumSum(grid, 0, j + 1, i, n - 1);
                s3 = minimumSum(grid, i + 1, j + 1, m - 1, n - 1);
                ans = std::min(ans, s1 + s2 + s3);
            }
            // 水平切左半块，枚举水平切的位置
            s1 = rightS;
            for (int i = 0; i < m - 1; ++i)
            {
                s2 = minimumSum(grid, 0, 0, i, j);
                s3 = minimumSum(grid, i + 1, 0, m - 1, j);
                ans = std::min(ans, s1 + s2 + s3);
            }
        }

        return ans;
    }

private:
    const int inf = 0x3f3f3f3f;
    std::unordered_map<int, int> memo;

    // 计算grid中以grid[ltx][lty]为左上角，grid[rbx][rby]为右下角的子矩形中包含所有1的最小矩形面积
    int minimumSum(const std::vector<std::vector<int>>& grid, int ltx, int lty, int rbx, int rby)
    {
        int key = hash(ltx, lty, rbx, rby);
        auto it = memo.find(key);
        if (it != memo.end())
            return it->second;

        bool coverOne = false;
        int top = inf, bottom = -1, left = inf, right = -1;
        for (int i = ltx; i <= rbx; ++i)
        {
            for (int j = lty; j <= rby; ++j)
            {
                if (grid[i][j])
                {
                    coverOne = true;
                    if (top == inf) top = i;
                    bottom = i;
                    if (j < left) left = j;
                    if (j > right) right = j;
                }
            }
        }
        int res;
        if (coverOne)
            res = (bottom - top + 1) * (right - left + 1);
        else
            res = inf;
        return memo[key] = res;
    }

    int hash(int a, int b, int c, int d)
    {
        return a * 1000000 + b * 10000 + c * 100 + d;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
