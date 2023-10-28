#include <iostream>
#include <vector>
#include <bitset>
#include "../debug/debug.h"

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

        debug::printVector2D(dp);

        return dp[text1.size()][text2.size()];
    }
};

class Solution2
{
public:
    struct BitSet
    {
        using uint64 = unsigned long long;

        static constexpr int MAX_N{1000};
        std::vector<uint64> t;

        BitSet() : t(MAX_N / 64 + 5) {}

        int count()
        {
            int ret = 0;
            for (int v : t)
            {
                ret += __builtin_popcountll(v);
            }
            return ret;
        }

        void set(int p)
        {
            t[p >> 6] |= 1llu << (p & 63);
        }

        void shift()
        {
            uint64 last = 0;
            for (int i = 0; i < t.size(); ++i)
            {
                uint64 cur = t[i] >> 63;
                (t[i] <<= 1) |= last;
                last = cur;
            }
        }

        BitSet& operator|=(const BitSet &rhs)
        {
            for (int i = 0; i < t.size(); ++i)
            {
                t[i] |= rhs.t[i];
            }
            return *this;
        }

        BitSet& operator&=(const BitSet &rhs)
        {
            for (int i = 0; i < t.size(); ++i)
            {
                t[i] &= rhs.t[i];
            }
            return *this;
        }

        BitSet& operator^=(const BitSet &rhs)
        {
            for (int i = 0; i < t.size(); ++i)
            {
                t[i] ^= rhs.t[i];
            }
            return *this;
        }

        BitSet& operator=(const BitSet &rhs)
        {
            for (int i = 0; i < t.size(); ++i)
            {
                t[i] = rhs.t[i];
            }
            return *this;
        }

        BitSet operator-(const BitSet &rhs)
        {
            uint64 last = 0;
            BitSet ret;
            for (int i = 0; i < t.size(); ++i)
            {
                uint64 cur = (t[i] < rhs.t[i] + last);
                ret.t[i] = t[i] - rhs.t[i] - last;
                last = cur;
            }
            return ret;
        }
    };

    int longestCommonSubsequence(std::string text1, std::string text2)
    {
        int n = text1.size(), m = text2.size();

        std::vector<BitSet> p(26);
        BitSet f, g;
        for (int i = 0; i < n; ++i)
        {
            p[text1[i] - 'a'].set(i + 1);
        }
        for (int i = 0; i < m; ++i)
        {
            (g = f) |= p[text2[i] - 'a'];
            f.shift();
            f.set(0);
            ((f = g - f) ^= g) &= g;
        }
        return f.count();
    }
};

std::bitset<8> subtractBitsets(const std::bitset<8>& a, const std::bitset<8>& b) {
    std::bitset<8> result;
    bool borrow = false;

    for (int i = 0; i < 8; ++i) {
        bool bitA = a[i];
        bool bitB = b[i];

        // 处理进位
        if (borrow) {
            if (bitA) {
                bitA = false; // a[i] = 1, borrow = 1，将a[i]设为0
            } else {
                bitA = true;  // a[i] = 0, borrow = 1，将a[i]设为1
                borrow = false;
            }
        }

        // 计算差值
        if (bitA && !bitB) {
            result[i] = true;
        } else if (!bitA && bitB) {
            if (!borrow) {
                result[i] = true;
            }
            borrow = true;
        }
    }

    return result;
}

int main()
{
    Solution solution;
    std::string text1("abcde"), text2("ace");
    int ans = solution.longestCommonSubsequence(text1, text2);
    logObj(ans);

    std::bitset<8> a("11011010");
    std::bitset<8> b("01110101");

    std::bitset<8> difference = subtractBitsets(a, b);

    std::cout << "a - b = " << difference << std::endl;


    return 0;
}
