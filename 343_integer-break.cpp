#include <iostream>
#include <vector>

class Solution
{
public:
    int integerBreak(int n)
    {
        //dp[i]:数i拆分为k(k >= 2)个正整数后，最大的乘积是多少
        int dp[MAX_N];
        // 初始化，dp[0]、dp[1]无意义
        dp[2] = 1;
        dp[3] = 2;
        for (int i = 4; i <= n; ++i)
        {
            dp[i] = i - 1;
            for (int j = 2; j <= i / 2; ++j)
            {
                dp[i] = std::max(j * std::max(dp[i - j], i - j), dp[i]);
            }
        }

        for (int i = 2; i <= n; ++i)
        {
            std::cout << i << '\t';
        }
        std::cout << std::endl;
        for (int i = 2; i <= n; ++i)
        {
            std::cout << dp[i] << "\t";
        }
        std::cout << std::endl;
        return dp[n];
    }

private:
    const int MAX_N{59};
};

class Solution2
{
public:
    int integerBreak(int n)
    {
        if (n == 2) return 1;
        if (n == 3) return 2;
        if (n == 4) return 4;

        int result = 1;
        while (n > 4)
        {
            result *= 3;
            n -= 3;
        }
        result *= n;
        return result;
    }
};

int main()
{
    int n;
    std::cin >> n;
    Solution solution;
    int result = solution.integerBreak(n);
    std::cout << result << std::endl;
    return 0;
}
