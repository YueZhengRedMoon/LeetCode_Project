#include <iostream>
#include <algorithm>
#include <vector>
#include "../debug/debug.h"

class Solution
{
public:
    int countKSubsequencesWithMaxBeauty(std::string s, int k)
    {
        if (k > 26)
            return 0;

        int f[26]{};
        for (int c : s)
            ++f[c - 'a'];
        std::sort(std::begin(f), std::end(f), std::greater<int>());

        std::vector<std::pair<int, int>> fKind({std::make_pair(f[0], 1)});
        int totalKind = 1;
        for (int i = 1; i < 26 && f[i] != 0; ++i)
        {
            ++totalKind;
            if (f[i] == fKind.back().first)
                ++fKind.back().second;
            else
                fKind.emplace_back(f[i], 1);
        }
        if (totalKind < k)
            return 0;

        const int MOD = 1e9 + 7;
        int kind = 0;
        long long ans = 1;
        for (auto [freq, cnt] : fKind)
        {
            if (kind + cnt <= k)
            {
                // ans = ans * pow(freq, cnt)
                ans = ans * quickPowMod(freq, cnt, MOD) % MOD;
                kind += cnt;
            }
            else
            {
                int remain = k - kind;
                if (remain)
                {
                    // ans = ans * comb(cnt, remain) * pow(freq, remain)
                    ans = (ans * comb(cnt, remain, MOD) % MOD) * quickPowMod(freq, remain, MOD) % MOD;
                }
                break;
            }
        }

        return (int) ans;
    }

private:
    long long quickPowMod(long long x, long long n, long long mod)
    {
        long long res = 1;
        while (n)
        {
            if (n & 1)
                res = res * x % mod;
            x = x * x % mod;
            n >>= 1;
        }
        return res;
    }

    long long comb(long long n, long long m, long long mod)
    {
        if (n < m)
            return 0;
        if (m == 0 || m == n)
            return 1;

        long long res = 1;
        for (long long i = 1; i <= m; ++i)
        {
            res = (res * (n - i + 1) % mod) / i;
        }

        return res;
    }
};

int main()
{
    Solution solution;
    std::string s = "bcca";
    int k = 2;
    int ans = solution.countKSubsequencesWithMaxBeauty(s, k);
    logObj(ans);
    return 0;
}
