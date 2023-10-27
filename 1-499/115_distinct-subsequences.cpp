#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int numDistinct(std::string s, std::string t)
    {
        // 如果s的长度小于t的长度，则s的子序列中不可能出现t
        if (s.size() < t.size())
        {
            return 0;
        }

        // dp[i][j]:s[0:j-1]的子序列中t[0:i-1]的出现次数
        std::vector<std::vector<int>> dp(t.size() + 1, std::vector<int>(s.size() + 1, 0));
        for (int i = 0; i <= s.size(); ++i)
        {
            dp[0][i] = 1;
        }

        // 递推公式：
        // 如果t[i-1]==s[j-1]，则dp[i][j] = dp[i][j-1] + dp[i-1][j-1]
        // 否则dp[i][j] = dp[i][j-1]
        for (int i = 1; i <= t.size(); ++i)
        {
            for (int j = i; j <= s.size(); ++j)
            {
                dp[i][j] = dp[i][j - 1];
                if (t[i - 1] == s[j - 1] && (std::numeric_limits<int>::max() - dp[i][j] >= dp[i - 1][j - 1]))
                {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }

        return dp[t.size()][s.size()];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
