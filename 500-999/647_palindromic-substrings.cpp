#include <iostream>
#include <vector>

class Solution
{
public:
    int countSubstrings(std::string s)
    {
        int len = s.size();
        // dp[i][j]:s[i:j]是否是回文串
        std::vector<std::vector<bool>> dp(len, std::vector<bool>(len, false));

        int result = 0;
        for (int i = len - 1; i >= 0; --i)
        {
            dp[i][i] = true;
            ++result;
            for (int j = i + 1; j < len; ++j)
            {
                if (s[i] == s[j])
                {
                    if (j - i == 1)
                    {
                        dp[i][j] = true;
                        ++result;
                    }
                    else
                    {
                        if (dp[i + 1][j - 1])
                        {
                            dp[i][j] = true;
                            ++result;
                        }
                    }
                }
            }
        }

        return result;
    }
};

class Solution2
{
public:
    int countSubstrings(std::string s)
    {
        int result = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            result += extend(s, i, i);
            result += extend(s, i, i + 1);
        }
        return result;
    }

private:
    int extend(const std::string &s, int i, int j)
    {
        int result = 0;
        while (i >= 0 && j < s.size() && s[i] == s[j])
        {
            --i;
            ++j;
            ++result;
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}