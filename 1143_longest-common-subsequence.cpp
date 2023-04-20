#include <iostream>
#include <vector>

class Solution
{
public:
    int longestCommonSubsequence(std::string text1, std::string text2)
    {
        // dp[i][j]:以text1[i-1]结尾和以text2[i-1]结尾的字符串的最长公共子序列的长度
        std::vector<std::vector<int>> dp(text1.size() + 1, std::vector<int>(text2.size() + 1, 0));

        for (int i = 1; i <= text1.size(); ++i)
        {
            for (int j = 1; j <= text2.size(); ++j)
            {
                if (text1[i - 1] == text2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }

        return dp[text1.size()][text2.size()];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
