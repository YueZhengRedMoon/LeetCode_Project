#include <iostream>
#include <vector>

class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        std::vector<int> dp(n, 1);
        for (int j = 1; j < m; ++j)
        {
            for (int i = 1; i < n; ++i)
            {
                // dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
                // 重用列:dp[i] = dp[i - 1] + dp[i]
                dp[i] += dp[i - 1];
            }
        }
        return dp[n - 1];
    }
};

class Solution2
{
public:
    int uniquePaths(int m, int n)
    {
        long long numerator = 1;      // 分子
        int denominator = m - 1;    // 分母
        int count = m - 1;
        int t = m + n - 2;
        // 组合数的计算公式：
        // 从n个数中取出m个数有C(n, m) = A(n, m) / m! = n! / (m! * (n - m)!)
        // = n * (n - 1) * ... * (n - m + 1) * (n - m)! / (m! * (n - m)!)
        // = n * (n - 1) * ... * (n - m + 1) / m!

        /** 会溢出
        // 计算分子
        while (count--)
        {
            numerator *= t;
            --t;
        }

        // 计算分母
        for (int i = 1; i <= m - 1; ++i)
        {
            denominator *= i;
        }

        return numerator / denominator;
        */

        while (count--)
        {
            numerator *= t;
            --t;
            while (denominator != 0 && numerator % denominator == 0)
            {
                numerator /= denominator;
                --denominator;
            }
        }

        return numerator;
    }
};

// 计算组合数C(n, m)：从n个数中取出m种数有多少种取法
int C(int n, int m)
{
    if (m > n) return 0;
    if (m == 0 || m == n) return 1;

    // 定义二维数组dp，dp[i][j]表示从i个数中取出j个数有多少种取法
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    // 初始化dp数组
    for (int i = 0; i <= n; ++i)
    {
        dp[i][0] = 1;
    }

    // 组合数递推公式：C(n, m) = C(n - 1, m - 1) + C(n - 1, m)
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= std::min(i, m); ++j)
        {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }

    return dp[n][m];
}

long long C2(int n, int k)
{
    if (k == 0 || k == n) {
        return 1;
    }

    long long Cnk = 1;
    for (int i = 1; i <= k; i++) {
        Cnk = Cnk * (n - i + 1) / i;
    }

    return Cnk;
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    int n, m;
    std::cin >> n >> m;
    std::cout << C(n, m) << std::endl;
    std::cout << C2(n, m) << std::endl;
    return 0;
}
