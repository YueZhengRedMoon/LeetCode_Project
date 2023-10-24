#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> constructProductMatrix(std::vector<std::vector<int>> &grid)
    {
        const int MOD = 12345;
        int n = grid.size(), m = grid[0].size();
        // rowPrefix[i]:grid[0:i-1]的所有元素的乘积，rowSuffix[i]:grid[i+1:n-1]的所有元素的乘积
        std::vector<long long> rowPrefix(n, 1), rowSuffix(n, 1);
        // colPrefix[i][j]:grid[i][0:j-1]所有元素的乘积
        std::vector<std::vector<long long>> colPrefix(n, std::vector<long long>(m, 1));
        // colSuffix[i][j]:grid[i][j+1:n-1]所有元素的乘积
        std::vector<std::vector<long long>> colSuffix(n, std::vector<long long>(m, 1));

        // 计算前缀
        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j < m; ++j)
                colPrefix[i][j] = colPrefix[i][j - 1] * grid[i][j - 1] % MOD;
            if (i > 0)
                rowPrefix[i] = (rowPrefix[i - 1] * colPrefix[i - 1][m - 1] % MOD) * grid[i - 1][m - 1] % MOD;
        }

        // 计算后缀
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = m - 2; j >= 0; --j)
                colSuffix[i][j] = colSuffix[i][j + 1] * grid[i][j + 1] % MOD;
            if (i < n - 1)
                rowSuffix[i] = (rowSuffix[i + 1] * colSuffix[i + 1][0] % MOD) * grid[i + 1][0] % MOD;
        }

        // 构造乘积矩阵
        std::vector<std::vector<int>> ans(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                ans[i][j] = (int )((rowPrefix[i] * rowSuffix[i] % MOD) * colPrefix[i][j] % MOD) * colSuffix[i][j] % MOD;
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> constructProductMatrix(std::vector<std::vector<int>> &grid)
    {
        const int MOD = 12345;
        int n = grid.size(), m = grid[0].size();
        std::vector<std::vector<int>> p(n, std::vector<int>(m));

        long long suf = 1;  // 后缀乘积
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = m - 1; j >= 0; --j)
            {
                p[i][j] = suf;
                suf = suf * grid[i][j] % MOD;
            }
        }

        long long pre = 1;  // 前缀乘积
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                p[i][j] = p[i][j] * pre % MOD;
                pre = pre * grid[i][j] % MOD;
            }
        }

        return p;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}