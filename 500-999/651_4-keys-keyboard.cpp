#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Solution
{
public:
    int maxA(int n)
    {
        if (n <= 3) return n;
        // dp[i][j].first：第j次按键通过第i种操作最多能输出几个A，以及此时剪贴板中A的数量
        // i = 0:直接输入A i = 1:粘贴剪贴板中的内容 i = 2:全选、复制、粘贴
        std::vector<std::vector<std::pair<int, int>>> dp(3, std::vector<std::pair<int, int>>(n));
        for (int j = 0; j < 3; ++j)
        {
            dp[0][j].first = j + 1;
            dp[0][j].second = 0;
            dp[1][j].first = 0;
            dp[1][j].second = 0;
            dp[2][j].first = 0;
            dp[2][j].second = 0;
        }

        for (int j = 3; j < n; ++j)
        {
            // 第j步输入A
            dp[0][j].first = std::max({dp[0][j - 1].first, dp[1][j - 1].first, dp[2][j - 1].first});
            dp[0][j].second = 0;
            for (int i = 0; i < 3; ++i)
            {
                if (dp[i][j - 1].first == dp[0][j].first && dp[i][j - 1].second > dp[0][j].second)
                {
                    dp[0][j].second = dp[i][j - 1].second;
                }
            }
            ++dp[0][j].first;

            // 第j步粘贴
            dp[1][j].first = 0;
            dp[1][j].second = 0;
            for (int i = 0; i < 3; ++i)
            {
                int cnt = dp[i][j - 1].first + dp[i][j - 1].second;
                if (cnt > dp[1][j].first)
                {
                    dp[1][j].first = cnt;
                    dp[1][j].second = dp[i][j - 1].second;
                }
                else if (cnt == dp[1][j].first && dp[1][j].second < dp[i][j - 1].second)
                {
                    dp[1][j].second = dp[i][j - 1].second;
                }
            }

            // 第j步全选、复制、粘贴
            dp[2][j].first = 0;
            dp[2][j].second = 0;
            for (int i = 0; i < 3; ++i)
            {
                int cnt = dp[i][j - 3].first * 2;
                if (cnt > dp[2][j].first)
                {
                    dp[2][j].first = cnt;
                    dp[2][j].second = dp[i][j - 3].first;
                }
            }
        }

        return std::max({dp[0][n - 1].first, dp[1][n - 1].first, dp[2][n - 1].first});
    }
};

class Solution2
{
public:
    int maxA(int n)
    {
        // dp[i]:通过i次按键最多能输出几个'A'
        std::vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + 1;  // 直接输入'A'
            for (int j = 0; j < i - 1; ++j)
            {
                // 当j == i - 2时：i-2全选，i-1复制,i粘贴
                dp[i] = std::max(dp[i], dp[j] * (i - j - 1));
            }
        }
        return dp[n];
    }
};

int main()
{
    Solution solution1;
    Solution2 solution2;
    int n = 76;
    int ans1 = solution1.maxA(n);
    int ans2 = solution2.maxA(n);
    std::cout << ans1 << std::endl;
    std::cout << ans2 << std::endl;
    return 0;
}