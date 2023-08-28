#include <iostream>
#include <cstring>

class Solution
{
public:
    int countAnagrams(std::string s)
    {
        constexpr int MOD = 1e9 + 7;
        long long ans = 1ll, mul = 1ll;
        int cnt[26]{0};
        int i = 1;
        for (char c : s)
        {
            if (c == ' ')
            {
                std::memset(cnt, 0, sizeof(cnt));
                i = 1;
                continue;
            }

            ans = ans * (i++) % MOD;
            mul = mul * (++cnt[c - 'a']) % MOD;
        }
        return ans * quickPowMod(mul, MOD - 2, MOD) % MOD;
    }

private:
    long long quickPowMod(long long x, long long n, long long mod)
    {
        long long res = 1;
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
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
