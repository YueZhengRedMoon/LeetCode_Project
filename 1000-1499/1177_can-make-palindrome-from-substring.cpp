#include <iostream>
#include <vector>
#include "../debug/debug.h"

/** 可以重新排列子串后再进行替换 */
class Solution
{
public:
    std::vector<bool> canMakePaliQueries(std::string s, std::vector<std::vector<int>> &queries)
    {
        int len = s.size();
        // dp[i][j]:s[i:j]中需要修改多少个字符才能使s[i:j]变为回文串
        std::vector<std::vector<int>> dp(len, std::vector<int>(len));

        for (int i = len - 2; i >= 0; --i)
        {
            dp[i][i + 1] = (s[i] != s[i + 1]);
            for (int j = i + 2; j < len; ++j)
            {
                dp[i][j] = dp[i + 1][j - 1] + (s[i] != s[j]);
            }
        }

        int n = queries.size();
        std::vector<bool> ans(n);
        for (int i = 0; i < n; ++i)
        {
            ans[i] = dp[queries[i][0]][queries[i][1]] <= queries[i][2];
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<bool> canMakePaliQueries(std::string s, std::vector<std::vector<int>> &queries)
    {
        int len = s.size();
        std::vector<std::vector<int>> prefix(26, std::vector<int>(len, 0));
        prefix[s[0] - 'a'][0] = 1;
        for (int i = 1; i < len; ++i)
        {
            for (int j = 0; j < 26; ++j)
            {
                prefix[j][i] = prefix[j][i - 1];
            }
            ++prefix[s[i] - 'a'][i];
        }

        std::vector<bool> ans;
        ans.reserve(queries.size());
        for (const auto &query : queries)
        {
            int left = query[0], right = query[1], k = query[2];
            int replace = 0;
            bool replaced = (right - left + 1) % 2 == 1;
            for (int i = 0; i < 26 && replace <= k; ++i)
            {
                int count = (left == 0 ? prefix[i][right] : prefix[i][right] - prefix[i][left - 1]);
                if (count % 2 == 1)
                {
                    if (replaced)
                    {
                        replaced = false;
                    }
                    else
                    {
                        ++replace;
                        replaced = true;
                    }
                }
            }
            ans.push_back(replace <= k);
        }

        return ans;
    }
};

class Solution3
{
public:
    std::vector<bool> canMakePaliQueries(std::string s, std::vector<std::vector<int>> &queries)
    {
        int n = s.size();
        // count[i]二进制表示的第j位表示s[0:i]中第j个小写字母出现的次数的奇偶性，=1表示出现奇数次，=0表示出现偶数次
        std::vector<int> count(n + 1);
        for (int i = 0; i < n; ++i)
        {
            count[i + 1] = count[i] ^ (1 << (s[i] - 'a'));
        }

        std::vector<bool> ans;
        ans.reserve(queries.size());
        for (const auto &query : queries)
        {
            int left = query[0], right = query[1], k = query[2];
            int bits = 0, x = count[right + 1] ^ count[left];
            // 统计x中1出现的次数，即s[left:right]中出现次数为奇数次的字母数
            // 每出现一种出现次数为奇数的字母，都需要要将其替换为另一种出现次数为奇数的字母
            // 如果s[left:right]的长度为奇数，则可以有一种出现次数为奇数的字母不用替换
            bool replaced = (right - left + 1) % 2 == 1;
            while (x > 0)
            {
                x &= x - 1;
                if (replaced)
                {
                    replaced = false;
                }
                else
                {
                    ++bits;
                    replaced = true;
                }
            }
            ans.push_back(bits <= k);
        }

        return ans;
    }
};

int main()
{
    Solution2 solution;
    std::string s = "abcda";
    std::vector<std::vector<int>> queries{{0, 3, 1}};
    std::vector<bool> ans = solution.canMakePaliQueries(s, queries);
    std::cout << std::boolalpha;
    debug::printVector(ans);
    return 0;
}