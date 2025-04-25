#include <iostream>
#include <vector>
#include <string_view>

class Solution
{
public:
    int longestPalindrome(std::string s, std::string t)
    {
        int sLen = s.size(), tLen = t.size();

        // s或t取空串的情况
        int ps = longestPalindrome(s);
        int pt = longestPalindrome(t);
        int ans = std::max(ps, pt);

        // 逆转字符串t
        for (int i = 0, j = tLen - 1; i < j; ++i, --j)
        {
            char c = t[i];
            t[i] = t[j];
            t[j] = c;
        }

        // 求s与逆转后的t的最长公共子串的长度
        //  -- f[i][j]:s[0, i)与t[0, j)中以s[i-1]结尾和以t[j-1]结尾的最长公共子串的长度
        std::vector<std::vector<int>> f(sLen + 1, std::vector<int>(tLen + 1));
        for (int i = 1; i <= sLen; ++i)
        {
            for (int j = 1; j <= tLen; ++j)
            {
                if (s[i - 1] == t[j - 1])
                {
                    f[i][j] = f[i - 1][j - 1] + 1;
                    int pLen = 2 * f[i][j]; // 回文串的长度
                    if (i < sLen || j < tLen)
                    {
                        ++pLen; // 构成长度为奇数的回文串
                    }
                    if (pLen > ans)
                        ans = pLen;
                }
                else
                {
                    f[i][j] = 0;
                }
            }
        }
        return ans;
    }

private:
    // 获取s中最长的回文子串的长度
    int longestPalindrome(std::string_view s)
    {
        int res = 1, len = s.size();
        for (int i = 0; i < len - 1; ++i)
        {
            int len1 = expandAroundCenter(s, i, i);         // 奇数长度的回文串
            int len2 = expandAroundCenter(s, i , i + 1);    // 偶数长度的回文串
            res = std::max(res, std::max(len1, len2));
        }
        return res;
    }

    // 以s[left, right]为中心最长回文子串的长度
    int expandAroundCenter(std::string_view s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {
            --left;
            ++right;
        }
        return right - left - 1;
    }
};

int main()
{
    std::string s = "jjh", t = "g";
    Solution solution;
    int ans = solution.longestPalindrome(s, t);
    std::cout << ans << std::endl;
    return 0;
}
