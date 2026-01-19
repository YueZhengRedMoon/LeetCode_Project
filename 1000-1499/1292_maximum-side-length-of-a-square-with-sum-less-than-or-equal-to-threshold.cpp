#include <iostream>
#include <vector>
#include "../debug/debug.h"

class Solution
{
public:
    int maxSideLength(std::vector<std::vector<int>>& mat, int threshold)
    {
        int m = mat.size(), n = mat[0].size();
        // 二维前缀和，prefix[i][j]:mat[0,i)[0,j)的元素和
        std::vector<std::vector<int>> prefix(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }

        // 计算以mat[i][j]为左上角，边长为s的正方形区域的元素和
        auto sum = [&](int i, int j, int side) -> int {
            int i2 = i + side, j2 = j + side;
            return prefix[i2][j2] - prefix[i][j2] - prefix[i2][j] + prefix[i][j];
        };

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int side = ans + 1; i + side <= m && j + side <= n; ++side)
                {
                    if (sum(i, j, side) <= threshold)
                    {
                        ans = side;
                    }
                }
            }
        }
        return ans;
    }
};

class MySolution
{
public:
    int maxSideLength(std::vector<std::vector<int>>& mat, int threshold)
    {
        int m = mat.size(), n = mat[0].size();
        // 二维前缀和，prefix[i][j]:mat[0,i)[0,j)的元素和
        std::vector<std::vector<int>> prefix(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
        debug::printVector2D(prefix);

        // 计算以mat[i][j]为左上角，边长为s的正方形区域的元素和
        auto sum = [&](int i, int j, int side) -> int {
            int i2 = i + side, j2 = j + side;
            return prefix[i2][j2] - prefix[i][j2] - prefix[i2][j] + prefix[i][j];
        };

        // 检查mat中是否有边长为side，且元素和<=threshold的正方形区域
        auto check = [&](int side) -> bool {
            for (int i = 0; i + side <= m; ++i)
            {
                for (int j = 0; j + side <= n; ++j)
                {
                    if (sum(i, j, side) <= threshold)
                    {
                        return true;
                    }
                }
            }
            return false;
        };

        int ans = 0, left = 1, right = std::min(m, n) + 1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (check(mid)) // mat中存在边长为mid的正方形区域，其元素和<=threshold
            {
                ans = mid;
                left = mid + 1; // 扩大边长
            }
            else    // mat中不存在边长为mid的正方形区域，其元素和<=threshold
            {
                right = mid;    // 缩小边长
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> mat = {{18, 70}, {61, 1}, {25, 85}, {14, 40}, {11, 96}, {97, 96}, {63, 45}};
    int threshold = 40184;
    int ans = solution.maxSideLength(mat, threshold);
    std::cout << ans << std::endl;
    return 0;
}