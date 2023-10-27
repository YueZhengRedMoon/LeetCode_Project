#include <iostream>
#include <vector>

class Solution
{
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3)
    {
        int s1Len = s1.size(), s2Len = s2.size(), s3Len = s3.size();
        if (s1Len + s2Len != s3Len) return false;

        // dp[i][j][k]:s1前i个字符与s2前j个字符是否可以构成s2[0:k],i + j = k
        bool dp[101][101][201] = {false};

        dp[0][0][0] = true;
        for (int i = 0; i < s1Len && s1[i] == s3[i]; ++i)
            dp[i + 1][0][i + 1] = true;
        for (int i = 0; i < s2Len && s2[i] == s3[i]; ++i)
            dp[0][i + 1][i + 1] = true;

        for (int i = 1; i <= s1Len; ++i)
        {
            for (int j = 1; j <= s2Len; ++j)
            {
                for (int k = 2; k <= s3Len; ++k)
                {
                    if (i + j != k) continue;

                    if (s1[i - 1] == s3[k - 1] && dp[i - 1][j][k - 1])
                    {
                        dp[i][j][k] = true;
                    }
                    else if (s2[j - 1] == s3[k - 1] && dp[i][j - 1][k - 1])
                    {
                        dp[i][j][k] = true;
                    }
                }
            }
        }

        return dp[s1Len][s2Len][s3Len];
    }
};

class Solution2
{
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3)
    {
        int s1Len = s1.size(), s2Len = s2.size(), s3Len = s3.size();
        if (s1Len + s2Len != s3Len || (s3.back() != s1.back() && s3.back() != s2.back()) || (s3[0] != s1[0] && s3[0] != s2[0]))
            return false;

        // dp[i][j]:s1的前i个元素与s2的前j个元素能否构成s3的前i+j个元素
        std::vector<std::vector<bool>> dp(s1Len + 1, std::vector<bool>(s2Len + 1, false));

        dp[0][0] = true;
        for (int i = 0; i < s1Len && s1[i] == s3[i]; ++i)
            dp[i + 1][0] = true;
        for (int j = 0; j < s2Len && s2[j] == s3[j]; ++j)
            dp[0][j + 1] = true;

        for (int i = 1; i <= s1Len; ++i)
        {
            for (int j = 1; j <= s2Len; ++j)
            {
                int k = i + j - 1;
                if (s1[i - 1] == s3[k] && dp[i - 1][j])
                {
                    dp[i][j] = true;
                }
                else if (s2[j - 1] == s3[k] && dp[i][j - 1])
                {
                    dp[i][j] = true;
                }
            }
        }

        return dp[s1Len][s2Len];
    }
};

class Solution3
{
public:
    bool isInterleave(std::string s1, std::string s2, std::string s3)
    {
        int s1Len = s1.size(), s2Len = s2.size(), s3Len = s3.size();
        if (s1Len + s2Len != s3Len || (s3.back() != s1.back() && s3.back() != s2.back()) || (s3[0] != s1[0] && s3[0] != s2[0]))
            return false;

        // dp[i][j]:s1的前i个元素与s2的前j个元素能否构成s3的前i+j个元素
        std::vector<bool> dp(s2Len + 1, false);

        dp[0] = true;
        for (int j = 0; j < s2Len && s2[j] == s3[j]; ++j)
            dp[j + 1] = true;

        for (int i = 1; i <= s1Len; ++i)
        {
            for (int j = 1; j <= s2Len; ++j)
            {
                int k = i + j - 1;
                if (s1[i - 1] == s3[k] && dp[j])
                {
                    dp[j] = true;
                }
                else if (s2[j - 1] == s3[k] && dp[j - 1])
                {
                    dp[j] = true;
                }
                else
                {
                    dp[j] = false;
                }
            }
        }

        return dp[s2Len];
    }
};

int main()
{
    Solution solution;
    std::string s1 = "aabcc";
    std::string s2 = "dbbca";
    std::string s3 = "aadbbbaccc";
    bool ans = solution.isInterleave(s1, s2, s3);
    std::cout << std::boolalpha;
    std::cout << ans << std::endl;
    return 0;
}
