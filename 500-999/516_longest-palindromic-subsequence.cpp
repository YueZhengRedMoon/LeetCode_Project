#include <iostream>
#include <vector>

class Solution
{
public:
    int longestPalindromeSubseq(std::string s)
    {
        int len = s.size();
        // dp[i][j]:s[i:j]的最长回文子序列的长度
        std::vector<std::vector<int>> dp(len, std::vector<int>(len, 0));

        for (int i = len - 1; i >= 0; --i)
        {
            for (int j = i; j < len; ++j)
            {
                if (s[i] == s[j])
                {
                    if (j - i <= 1)
                    {
                        dp[i][j] = j - i + 1;
                    }
                    else
                    {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    }
                }
                else
                {
                    dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[0][len - 1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}