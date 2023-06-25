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

int main()
{

    return 0;
}