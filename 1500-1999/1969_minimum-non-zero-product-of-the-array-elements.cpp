#include <iostream>
#include <vector>

class Solution
{
public:
    int minNonZeroProduct(int p)
    {
        return (((1LL << p) - 1) % MOD) * quickPowMod((1LL << p) - 2, (1LL << (p - 1)) - 1) % MOD;
    }

private:
    const int MOD = 1e9 + 7;

    long long quickPowMod(long long x, long long n)
    {
        x %= MOD;
        long long res = 1;
        while (n)
        {
            res = res * x % MOD;    // 由于n每个二进制位都是1，所以省去了判断1的if
            x = x * x % MOD;
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
