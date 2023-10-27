#include <iostream>
#include <unordered_map>
#include <vector>

/*
long long quickPowMod(long long x, long long n, long long mod)
{
    int res = 1;
    while (n)
    {
        if (n & 1)
        {
            res = res * x % mod;
        }
        n >>= 1;
        x = x * x % mod;
    }
    return res;
}

constexpr int MOD = 1e9 + 7;
constexpr int MAX_N = 1e4 + 1;
long long fact[MAX_N];
int init = [](){
    fact[0] = 1;
    for (int i = 1; i < MAX_N; ++i)
    {
        fact[i] = fact[i - 1] * i % MOD;
    }
    return 0;
}();

class Solution2
{
public:
    int countGoodSubsequences(std::string s)
    {
        std::vector<int> cnt(26, 0);
        int maxCnt = 0;
        for (char c : s)
        {
            int index = c - 'a';
            if (++cnt[index] > maxCnt)
            {
                maxCnt = cnt[index];
            }
        }

        long long ans = 0;
        for (int i = 1; i <= maxCnt; ++i)
        {
            int cur = 1;
            for (int c : cnt)
            {
                if (c >= i)
                {
                    cur = cur * (comb(c, i) + 1) % MOD;
                }
            }
            ans = (ans + cur - 1) % MOD;
        }

        return ans;
    }

private:
    // 从n个数中取出m个数的组合数
    long long comb(long long n, long long m)
    {
        if (n < m)
            return 0;
        return divide(fact[n], fact[n - m] * fact[m] % MOD);
    }

    long long divide(long long x, long long y)
    {
        return x * inv(y) % MOD;
    }

    long long inv(long long x)
    {
        return quickPowMod(x, MOD - 2, MOD);
    }
};
*/

class Solution
{
public:
    Solution() : fact(MAX_N, 1), inv(MAX_N, 1)
    {
        for (int i = 2; i < MAX_N; ++i)
        {
            fact[i] = fact[i - 1] * i % MOD;
            inv[i] = quickPowMod(fact[i], MOD - 2);
        }
    }

    int countGoodSubsequences(std::string s)
    {
        std::unordered_map<char, int> count;
        int maxCount = 0;
        for (char c : s)
        {
            int &cnt = count[c];
            if (++cnt > maxCount)
            {
                maxCount = cnt;
            }
        }

        long long ans = 0;
        for (int i = 1; i <= maxCount; ++i) // 枚举每种字符的出现频率
        {
            long long cur = 1ll;
            for (const auto &it : count) // 枚举出现的每种字符
            {
                int cnt = it.second;   // 该种字符的出现次数
                cur = cur * (comb(cnt, i) + 1) % MOD;   // 1是该字符一个都不取的情况
            }
            ans = (ans + cur - 1) % MOD;    // 减去的1是空子序列
        }

        return (int)ans;
    }

private:
    static constexpr int MOD{1000000007};
    static constexpr int MAX_N{10001};
    std::vector<long long> fact;  // 阶乘
    std::vector<long long> inv;   // 逆元

    long long quickPowMod(long long x, long long n)
    {
        long long res = 1ll;
        while (n)
        {
            if (n & 1)
            {
                res = res * x % MOD;
            }
            x = x * x % MOD;
            n >>= 1;
        }
        return res;
    }

    // 从n个数中取出m个数的组合数
    long long comb(int n, int m)
    {
        if (n < m)
            return 0;   // n < m，从n个数中无法取出m个数
        return fact[n] * inv[m] % MOD * inv[n - m] % MOD;
    }
};

int main()
{
    return 0;
}
