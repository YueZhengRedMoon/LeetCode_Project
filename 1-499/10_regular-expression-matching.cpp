#include <iostream>
#include <vector>

class Solution
{
public:
    bool isMatch(std::string s, std::string p)
    {
        // 检查s[i-1]是否与p[j-1]匹配(i从0开始，j从1开始)
        auto matches = [&](int i, int j) -> bool {
            return i && (p[j - 1] == '.' || s[i - 1] == p[j - 1]);
        };

        int m = s.size(), n = p.size();
        // f[i][j]:s[0, i)与s[0, j)是否匹配
        std::vector<std::vector<bool>> f(m + 1, std::vector<bool>(n + 1, false));
        f[0][0] = true; // 当s与p都为空串时可以匹配成功

        for (int i = 0; i <= m; ++i)    // i必须从0开始遍历，因为空串可以与a*,a*b*,a*b*c*...匹配成功
        {
            for (int j = 1; j <= n; ++j)
            {
                if (p[j - 1] != '*')
                {
                    // 当p当前字符不为'*'时s[0, i-1)与p[0, j-1]匹配，且s[i-1]与p[j-1]匹配
                    f[i][j] = matches(i, j) && f[i - 1][j - 1]; // 注意要先在matches中判断i是否>0
                }
                else
                {
                    // p当前字符(p[j-1])为*时
                    // (1)要么x*匹配0个字符即f[i][j-2]匹配
                    // (2)要么s[0,i-1)已经与p[0, j)匹配，进一步检查s[i-1]与p[j-2]是否匹配（匹配多个字符）。
                    f[i][j] = f[i][j - 2] || (matches(i, j - 1) && f[i - 1][j]);    // 注意要先在matches中判断i是否>0
                }
            }
        }

        return f[m][n];
    }
};

class Solution2
{
public:
    bool isMatch(std::string s, std::string p)
    {
        int m = s.size(), n = p.size();
        // f[i][j]:s[0, i)与s[0, j)是否匹配
        std::vector<std::vector<bool>> f(m + 1, std::vector<bool>(n + 1, false));
        f[0][0] = true; // 当s与p都为空串时可以匹配成功
        for (int i = 0; i <= m; ++i)    // i必须从0开始遍历，因为空串可以与a*,a*b*,a*b*c*...匹配成功
        {
            for (int j = 1; j <= n; ++j)
            {
                // 如果p下一个字符是 '*'，且当前字符不是*，则代表当前字符不能被单独使用，跳过
                if (j < n && p[j] == '*' && p[j - 1] != '*')
                    continue;

                if (i - 1 >= 0 && p[j - 1] != '*')
                {
                    // s与p对应字符匹配或p当前字符为.
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
                else if (p[j - 1] == '*')
                {
                    // p当前字符(p[j-1])为*时
                    // (1)要么x*匹配0个字符即f[i][j-2]匹配
                    // (2)要么s[0,i-1)已经与p[0, j)匹配，进一步检查s[i-1]与p[j-2]是否匹配（匹配多个字符）。
                    f[i][j] = (j - 2 >= 0 && f[i][j - 2]) || (i - 1 >= 0 && f[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                }
            }
        }
        return f[m][n];
    }
};



namespace WrongAnswer
{
    class Solution
    {
    public:
        bool isMatch(std::string s, std::string p)
        {
            int sLen = s.size(), pLen = p.size();
            std::vector<std::vector<int>> memo(sLen, std::vector<int>(pLen, -1));
            return isMatch(s, 0, p, 0, memo);
        }

    private:
        bool isMatch(const std::string& s, int si, const std::string& p, int pi, std::vector<std::vector<int>>& memo)
        {
            int sLen = s.size(), pLen = p.size();
            if (si == sLen && pi == pLen)
                return true;
            else if (sLen == si)
            {
                if (pi == pLen)
                {
                    return p[pi - 1] == '*';
                }
                else
                {
                    while (pi < pLen)
                        if (p[pi] != '*')
                            return false;
                    return true;
                }
            }
            else if (pi == pLen)
            {
                return p[pi - 1] == '*';
            }
            if (memo[si][pi] != -1)
                return memo[si][pi];

            int& res = memo[si][pi];
            if (s[si] == p[pi] || p[pi] == '.')
                return res = isMatch(s, si + 1, p, pi + 1, memo);
            else if (p[pi] == '*')
            {
                for (int i = si; i < sLen; ++i)
                {
                    if (isMatch(s, i, p, pi + 1, memo))
                    {
                        res = 1;
                        return true;
                    }
                }
            }
            res = 0;
            return false;
        }
    };
}

int main()
{
    Solution solution;
    std::string s = "ab", p = ".*";
    bool ans = solution.isMatch(s, p);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
