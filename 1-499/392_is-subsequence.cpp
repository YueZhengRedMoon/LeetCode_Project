#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
    bool isSubsequence(std::string s, std::string t)
    {
        if (s.empty())
        {
            return true;
        }

        for (int i = 0, j = 0; i < t.size(); ++i)
        {
            if (t[i] == s[j])
            {
                ++j;
            }
            if (j == s.size())
            {
                return true;
            }
        }

        return false;
    }
};

class Solution2
{
public:
    bool isSubsequence(std::string s, std::string t)
    {
        // dp[i][j]:以s[i]为结尾的子串与以t[j]为结尾的子串的最长公共子序列的长度
        std::vector<std::vector<int>> dp(s.size() + 1, std::vector<int>(t.size() + 1, 0));

        for (int i = 1; i <= s.size(); ++i)
        {
            for (int j = 1; j <= t.size(); ++j)
            {
                if (s[i - 1] == t[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = dp[i][j - 1], dp[i - 1][j];
                }

                std::cout << dp[i][j] << '\t';
            }
            std::cout << std::endl;
        }

        return dp[s.size()][t.size()] == s.size();
    }
};

int main()
{
    Solution2 solution2;
    if (solution2.isSubsequence("b", "c"))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }
    return 0;
}