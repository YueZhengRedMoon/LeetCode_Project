#include <iostream>
#include <vector>
#include "../debug/debug.h"

class Solution
{
public:
    int maxCollectedFruits(std::vector<std::vector<int>>& fruits)
    {
        int ans = 0, n = fruits.size();

        // 因为每个小朋友恰好走n-1次，左上角的小朋友只能走主对角线，主对角线上的所有水果一定会被收集
        for (int i = 0; i < n; ++i)
        {
            ans += fruits[i][i];
            fruits[i][i] = 0;   // 主对角线上的水果被收集
        }

        // f[i][j]:小朋友走到fruits[i][j]:最多能收集到多少水果
        // 将fruits矩阵按照2条对角线划分为上下左右4个区域
        // 因为每个小朋友恰好走n-1次，左下角的小朋友只能在下区移动，右上角的小朋友只能在右区活动
        std::vector<std::vector<int>> f(n, std::vector<int>(n));

        // DP计算左下角的小朋友可以收集到的水果数量
        auto isInDownArea = [&](int x, int y) -> bool {
            if (x >= n || y < 0)
                return false;

            if (y < n / 2)
            {
                return x >= n - 1 - y;
            }
            else    // y >= n / 2
            {
                return x >= y;
            }
        };

        f[n - 1][0] = fruits[n - 1][0];
        for (int j = 1; j < n; ++j)
        {
            for (int i = n - 1; i >= 0 && isInDownArea(i, j); --i)
            {
                // 从左上方(x, y)移动到(i, j)
                int x = i - 1, y = j - 1;
                if (isInDownArea(x, y))
                {
                    f[i][j] = f[x][y] + fruits[i][j];
                }

                // 从左方(x, y)移动到(i, j)
                x = i;
                y = j - 1;
                if (isInDownArea(x, y))
                {
                    f[i][j] = std::max(f[i][j], f[x][y] + fruits[i][j]);
                }

                // 从左下方(x, y)移动到(i, j)
                x = i + 1;
                y = j - 1;
                if (isInDownArea(x, y))
                {
                    f[i][j] = std::max(f[i][j], f[x][y] + fruits[i][j]);
                }
            }
        }
        ans += f[n - 1][n - 1];

        // DP计算右上角的小朋友可以收集到的水果数量
        auto isInRightArea = [&](int x, int y) -> bool {
            if (x < 0 || y >= n)
                return false;

            if (x < n / 2)
            {
                return y >= n - 1 - x;
            }
            else    // x >= n / 2
            {
                return y >= x;
            }
        };

        f[0][n - 1] = fruits[0][n - 1];
        for (int i = 1; i < n; ++i)
        {
            for (int j = n - 1; j >= 0 && isInRightArea(i, j); --j)
            {
                f[i][j] = 0;

                // 从左上方(x, y)移动到(i, j)
                int x = i - 1, y = j - 1;
                if (isInRightArea(x, y))
                {
                    f[i][j] = f[x][y] + fruits[i][j];
                }

                // 从上方(x, y)移动到(i, j)
                x = i - 1;
                y = j;
                if (isInRightArea(x, y))
                {
                    f[i][j] = std::max(f[i][j], f[x][y] + fruits[i][j]);
                }

                // 从从右上方(x, y)移动到(i, j)
                x = i - 1;
                y = j + 1;
                if (isInRightArea(x, y))
                {
                    f[i][j] = std::max(f[i][j], f[x][y] + fruits[i][j]);
                }
            }
        }
        ans += f[n - 1][n - 1];

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> fruits = {{8,5,0,17,15},{6,0,15,6,0},{7,19,16,8,18},{11,3,2,12,13},{17,15,15,4,6}};
    int ans = solution.maxCollectedFruits(fruits);
    std::cout << ans << std::endl;
    return 0;
}
