#include <iostream>
#include <algorithm>
#include <string_view>

class Solution
{
public:
    int longestSubsequence(std::string s, int k)
    {
        int n = s.size();

        // 将k转换为二进制字符串
        std::string kBinStr;
        while (k)
        {
            kBinStr.push_back(k & 1 ? '1' : '0');
            k >>= 1;
        }
        int kBinStrLen = kBinStr.size();
        if (n < kBinStrLen)
        {
            // s的长度<k的二进制表示字符串的长度，此时s表示的二进制字符串的值一定小于k，可以取整个字符串s
            return n;
        }
        // s的长度>=k的二进制表示字符串的长度将kBinStr逆序，并补上前导0，使其长度=s.size()
        std::reverse(kBinStr.begin(), kBinStr.end());
        kBinStr = std::string(n - kBinStrLen, '0') + kBinStr;

        // k的二进制表示的字符串的长度为kBinStrLen,则一定可以从s中取出长度为kBinStrLen-1的子序列，其值<=k
        int ans = kBinStrLen - 1;
        int left = kBinStrLen, right = n + 1;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (check(s, kBinStr, mid)) // 可以从s中取出长度为mid，且对应值<=k的子序列
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }

        return ans;
    }

private:
    // 检查从s中是否可以取出长度为len，且对应数字小于等于k的二进制子序列
    // kBinStr:k的二进制表示字符串，加上了前导0，以使其长度=s.size()
    bool check(std::string_view s, std::string_view kBinStr, int len)
    {
        std::string subSeq;
        subSeq.reserve(len);
        int n = s.size();
        for (int i = 0; i < n && subSeq.size() < len; ++i)
        {
            // s剩下的长度不够了，不能再贪心的只取0，剩下的所有字符串都加入到子序列中
            if (len - subSeq.size() == n - i)
            {
                subSeq += s.substr(i, n - i);
                break;
            }

            if (s[i] == '0')
            {
                subSeq.push_back('0');
            }
        }

        // 将k转换为长度为len的二进制字符串
        std::string_view kBinStrSuffix = kBinStr.substr(n - len);   // kBinStr去除掉前导0，使其长度变为len

        // 按字典序比较两个数的二进制字符串表示，避免subSeq过长，超出int的表示范围
        return subSeq <= kBinStrSuffix;
    }
};

class Solution2
{
public:
    int longestSubsequence(std::string s, int k)
    {
        int n = s.size(), m = 32 - __builtin_clz(k);    // m:k的二进制表示长度
        if (n < m)
        {
            return n;   //全选
        }

        int sufVal = std::stoi(s.substr(n - m), nullptr, 2);    // s（二进制表示）的后m位表示的值
        int ans = sufVal <= k ? m : m - 1;
        return ans + std::count(s.begin(), s.end() - m, '0');
    }
};

int main()
{
    Solution solution;
    std::string s(1, '0');
    int k = 583196182;
    int ans = solution.longestSubsequence(s, k);
    std::cout << "ans = " << ans << std::endl;
    return 0;
}
