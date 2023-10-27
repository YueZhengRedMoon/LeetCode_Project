#include <iostream>
#include <vector>
#include <limits>
#include <stack>

class Solution
{
public:
    int numSubmat(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        int sum = 0;

        for (int i = 0; i < m; ++i)
        {
            dp[i][0] = matrix[i][0];
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 1)
                {
                    int minLen = std::numeric_limits<int>::max();

                    if (j != 0)
                        dp[i][j] = dp[i][j - 1] + 1;    // 有多少连续1

                    for (int k = i; k >= 0 && dp[k][j] > 0; --k)
                    {
                        minLen = std::min(minLen, dp[k][j]);
                        sum += minLen;
                    }
                }
            }
        }

        return sum;
    }
};

class Solution2
{
public:
    int numSubmat(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<std::vector<int>> row(m, std::vector<int>(n, 0));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (j == 0)
                {
                    row[i][j] = matrix[i][j];
                }
                else if (matrix[i][j])
                {
                    row[i][j] = row[i][j - 1] + 1;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int min = row[i][j];
                for (int k = i; k >= 0 && row[k][j] > 0; --k)
                {
                    min = std::min(min, row[k][j]);
                    ans += min;
                }
            }
        }

        return ans;
    }
};

class Solution3
{
public:
    int numSubmat(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<std::vector<int>> row(m, std::vector<int>(n, 0));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (j == 0)
                {
                    row[i][j] = matrix[i][j];
                }
                else if (matrix[i][j])
                {
                    row[i][j] = row[i][j - 1] + 1;
                }
            }
        }

        int ans = 0;
        for (int j = 0; j < n; ++j)
        {
            int i = 0;
            int sum = 0;    // 以matrix[i][j]为右下角的全1子矩阵的数量
            std::stack<std::pair<int, int>> stack;
            while (i < m)
            {
                int height = 1;
                while (!stack.empty() && stack.top().first > row[i][j])
                {
                    std::pair<int, int> top = stack.top();
                    stack.pop();
                    // 弹出的时候要减去多余的答案
                    sum -= top.second * (top.first - row[i][j]);
                    height += top.second;
                }
                sum += row[i][j];
                ans += sum;
                stack.push({row[i][j], height});
                ++i;
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