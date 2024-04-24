#include <iostream>
#include <vector>
#include <stack>

class Solution
{
public:
    int maximalRectangle(std::vector<std::vector<char>>& matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        // left[i][j]:matrix[i][j]及其左边连续1的数量
        std::vector<std::vector<int>> left(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i)
        {
            left[i][0] = matrix[i][0] - '0';
            for (int j = 1; j < n; ++j)
            {
                if (matrix[i][j] == '1')
                    left[i][j] = 1 + left[i][j - 1];
            }
        }

        int ans = 0;
        for (int j = 0; j < n; ++j)
        {
            std::vector<int> up(m, 0), down(n, 0);
            std::stack<int> stack;
            for (int i = 0; i < m; ++i)
            {
                while (!stack.empty() && left[stack.top()][j] >= left[i][j])
                {
                    stack.pop();
                }
                up[i] = stack.empty() ? -1 : stack.top();
                stack.push(i);
            }

            stack = std::stack<int>();

            for (int i = m - 1; i >= 0; --i)
            {
                while (!stack.empty() && left[stack.top()][j] >= left[i][j])
                {
                    stack.pop();
                }
                down[i] = stack.empty() ? m : stack.top();
                stack.push(i);
            }

            for (int i = 0; i < m; ++i)
            {
                ans = std::max(ans, left[i][j] * (down[i] - up[i] - 1));
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    int maximalRectangle(std::vector<std::vector<char>>& matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        // left[i][j]:matrix[i][j]及其左边连续1的数量
        std::vector<std::vector<int>> left(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i)
        {
            left[i][0] = matrix[i][0] - '0';
            for (int j = 1; j < n; ++j)
            {
                if (matrix[i][j] == '1')
                    left[i][j] = 1 + left[i][j - 1];
            }
        }

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int k = i, w = left[k][j], h = 1; k >= 0 && matrix[k][j] == '1'; --k, ++h)
                {
                    w = std::min(w, left[k][j]);
                    ans = std::max(ans, w * h);
                }
            }
        }

        return ans;
    }
};

namespace WrongAnswer
{
    // 矩阵中的最大全1子矩形面积不具备单调性
    // 例如对于2 * 2的全1矩阵
    // 其中不可能找到面积为3的子矩形，不代表不存在面积为4的子矩形

    class Solution
    {
    public:
        int maximalRectangle(std::vector<std::vector<char>>& matrix)
        {
            int m = matrix.size(), n = matrix[0].size();
            // prefix[i][j]:左上角为matrix[0][0]，右下角为matrix[i-1][j-1]的矩形的元素和
            std::vector<std::vector<int>> prefix(m + 1, std::vector<int>(n + 1, 0));
            for (int i = 1; i <= m; ++i)
            {
                for (int j = 1; j <= n; ++j)
                {
                    prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + (matrix[i - 1][j - 1] - '0');
                }
            }
            // 左上角为matrix[ltx][lty],右下角为matrix[rbx][rby]的矩阵的元素和
            auto sum = [&prefix](int ltx, int lty, int rbx, int rby) -> int {
                return prefix[rbx + 1][rby + 1] - prefix[ltx][rby + 1] - prefix[rbx + 1][lty] + prefix[ltx][lty];
            };

            // 检查matrix中是否存在面积为s的全1矩形
            auto check = [&](int s) -> bool {
                for (int i = 0; i < m; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        for (int w = 1; w <= s; ++w)
                        {
                            if (s % w != 0)
                                continue;

                            int h = s / w;
                            if (i + h <= m && j + w <= n && sum(i, j, i + h - 1, j + w - 1) == s)
                                return true;
                        }
                    }
                }
                return false;
            };

            int left = 1, right = m * n, ans = 0;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (check(mid))
                {
                    ans = mid;
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }

            return ans;
        }
    };
}


int main()
{
    Solution2 solution;
    std::vector<std::vector<char>> matrix = {{'1', '0', '1', '0', '0'},
                                            {'1', '0', '1', '1', '1'},
                                            {'1', '1', '1', '1', '1'},
                                            {'1', '0', '0', '1', '0'}};
    std::vector<std::vector<char>> matrix2 = {{'1', '1'},
                                              {'1', '1'}};
    int ans = solution.maximalRectangle(matrix);
    std::cout << ans << std::endl;
    return 0;
}
