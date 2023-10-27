#include <iostream>
#include <vector>
#include <functional>

class MatrixSum
{
public:
    MatrixSum(const std::vector<std::string> &matrix) :
    row(matrix.size()), col(matrix[0].size()), sum(row + 1, std::vector<int>(col + 1, 0))
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + (matrix[i][j] == 'A');
            }
        }
    }

    // 左上角为(r1, c1)，右下角为(r2-1, c2-1)的子矩阵的元素和
    int query(int r1, int c1, int r2, int c2)
    {
        return sum[r2][c2] - sum[r2][c1] - sum[r1][c2] + sum[r1][c1];
    }

    bool hasApple(int r1, int c1, int r2, int c2)
    {
        return sum[r2][c2] - sum[r2][c1] - sum[r1][c2] + sum[r1][c1] > 0;
    }

private:
    int row;
    int col;
    std::vector<std::vector<int>> sum;
};

/** 会超时的递归 */
class Solution1
{
public:
    int ways(std::vector<std::string> &pizza, int k)
    {
        MatrixSum matrixSum(pizza);
        int m = pizza.size(), n = pizza[0].size();
        constexpr int MOD = 1e9 + 7;

        // 将左上角为(i, j)，右下角为(m-1, n-1)的披萨切c刀，使得每块披萨都有苹果的方案数
        std::function<int(int, int, int)> dfs = [&](int c, int i, int j) -> int
        {
            // 这整块披萨都没有苹果
            if (!matrixSum.hasApple(i, j, m, n))
            {
                return 0;
            }
            // 已经不能再切了，且当前披萨中有苹果，返回一种方案数
            if (c == 0)
            {
                return 1;
            }
            int res = 0;
            // 垂直切
            for (int j2 = j + 1; j2 < n; ++j2)
            {
                if (matrixSum.hasApple(i, j, m, j2))
                    res = (res + dfs(c - 1, i, j2)) % MOD;
            }
            // 水平切
            for (int i2 = i + 1; i2 < m; ++i2)
            {
                if (matrixSum.hasApple(i, j, i2, n))
                    res = (res + dfs(c - 1, i2, j)) % MOD;
            }
            return res;
        };

        return dfs(k - 1, 0, 0);
    }
};

/** 记忆化搜索 */
class Solution2
{
public:
    int ways(std::vector<std::string> &pizza, int k)
    {
        MatrixSum matrixSum(pizza);
        int m = pizza.size(), n = pizza[0].size();
        constexpr int MOD = 1e9 + 7;
        // 记忆化数组
        std::vector<std::vector<std::vector<int>>> memo(k, std::vector<std::vector<int>>(m, std::vector<int>(n, -1)));

        // 将左上角为(i, j)，右下角为(m-1, n-1)的披萨切c刀，使得每块披萨都有苹果的方案数
        std::function<int(int, int, int)> dfs = [&](int c, int i, int j) -> int
        {
            int &res = memo[c][i][j];
            // 已经计算过了，返回
            if (res != -1)
                return res;
            // 这整块披萨都没有苹果
            if (!matrixSum.hasApple(i, j, m, n))
            {
                return res = 0;
            }
            // 已经不能再切了，且当前披萨中有苹果，返回一种方案数
            if (c == 0)
            {
                return res = 1;
            }

            res = 0;
            // 垂直切
            for (int j2 = j + 1; j2 < n; ++j2)
            {
                if (matrixSum.hasApple(i, j, m, j2))
                    res = (res + dfs(c - 1, i, j2)) % MOD;
            }
            // 水平切
            for (int i2 = i + 1; i2 < m; ++i2)
            {
                if (matrixSum.hasApple(i, j, i2, n))
                    res = (res + dfs(c - 1, i2, j)) % MOD;
            }
            return res;
        };

        return dfs(k - 1, 0, 0);
    }
};

/** 自上而下记忆化搜索转自下而上动态规划 */
class Solution3
{
public:
    int ways(std::vector<std::string> &pizza, int k)
    {
        MatrixSum matrixSum(pizza);
        int m = pizza.size(), n = pizza[0].size();
        constexpr int MOD = 1e9 + 7;

        // dp[c][i][j]:将左上角为(i, j)，右下角为(m-1, n-1)的披萨切c刀，使得每块披萨都有苹果的方案数
        std::vector<std::vector<std::vector<int>>> dp(k, std::vector<std::vector<int>>(m, std::vector<int>(n, 0)));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                dp[0][i][j] = matrixSum.hasApple(i, j, m, n);
            }
        }

        for (int c = 1; c < k; ++c)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    // 水平切
                    for (int i2 = i + 1; i2 < m; ++i2)
                    {
                        if (matrixSum.hasApple(i, j, i2, n))
                            dp[c][i][j] = (dp[c][i][j] + dp[c - 1][i2][j]) % MOD;
                    }
                    // 垂直切
                    for (int j2 = j + 1; j2 < n; ++j2)
                    {
                        if (matrixSum.hasApple(i, j, m, j2))
                            dp[c][i][j] = (dp[c][i][j] + dp[c - 1][i][j2]) % MOD;
                    }
                }
            }
        }

        return dp[k - 1][0][0];
    }
};

class Solution4
{
public:
    int ways(std::vector<std::string> &pizza, int k)
    {
        int m = pizza.size(), n = pizza[0].size();
        constexpr int MOD = 1e9 + 7;
        // 二维后缀和，sum[i][j]表示左上角为(i, j)，右下角为(m-1, n-1)的子矩阵的元素和
        std::vector<std::vector<int>> sum(m + 1, std::vector<int>(n + 1, 0));
        // dp[c][i][j]:将左上角为(i, j)，右下角为(m-1, n-1)的披萨切c刀，使得每块披萨都有苹果的方案数
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                sum[i][j] = sum[i][j + 1] + sum[i + 1][j] - sum[i + 1][j + 1] + (pizza[i][j] == 'A');
                if (sum[i][j])
                    dp[i][j] = 1;
            }
        }

        while (--k)
        {
            std::vector<int> colSum(n); // colSum[j]:dp第j列的后缀和
            for (int i = m - 1; i >= 0; --i)
            {
                int rowSum = 0; // dp[i]的后缀和
                for (int j = n - 1; j >= 0; --j)
                {
                    int temp = dp[i][j];
                    if (sum[i][j] == sum[i][j + 1]) // 左边界没有苹果
                        dp[i][j] = dp[i][j + 1];
                    else if (sum[i][j] == sum[i + 1][j])    // 上边界没有苹果
                        dp[i][j] = dp[i + 1][j];
                    else    // 左边界上边界都有苹果，无论怎么切都有苹果
                        dp[i][j] = (rowSum + colSum[j]) % MOD;
                    rowSum = (rowSum + temp) % MOD;
                    colSum[j] = (colSum[j] + temp) % MOD;
                }
            }
        }

        return dp[0][0];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
