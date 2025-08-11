#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> productQueries(int n, std::vector<std::vector<int>>& queries)
    {
        std::vector<int> powers;
        for (int i = 0, t = n; t > 0; ++i, t >>= 1)
        {
            int p = 1 << i;
            if (p & n)
            {
                powers.push_back(p);
            }
        }

        const int MOD = 1'000'000'007;
        // prefix[i] = (powers[0] * powers[1] * ... * powers[i - 1]) % MOD
        std::vector<long long> prefix(powers.size() + 1);
        prefix[0] = 1;
        for (int i = 1; i <= powers.size(); ++i)
        {
            prefix[i] = (prefix[i - 1] * powers[i - 1]) % MOD;
        }

        std::vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            int l = queries[i][0], r = queries[i][1];
            // ans[i] = prefix[r+1] / prefix[l]
            ans[i] = (int) (prefix[r + 1] * quickPowMod(prefix[l], MOD - 2, MOD) % MOD);
        }
        return ans;
    }

private:
    // 计算x^n % m
    long long quickPowMod(long long x, long long n, long long m)
    {
        long long res = 1;
        while (n)
        {
            if (n & 1)
            {
                res = (res * x) % m;
            }
            x = (x * x) % m;
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
