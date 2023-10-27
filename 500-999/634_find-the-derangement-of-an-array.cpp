#include <iostream>
#include <vector>

class Solution
{
public:
    int findDerangement(int n)
    {
        // dp[i]:将i个数进行错位排列的方案数
        // 对于[1:i]，[2:i]的(i-1)个元素都可以放到第1个位置
        // 假设将第j个数(j!=1)固定到第1个位置，将第1个数交换到第j个位置，剩下(i-1)个数错位排列的方案数是k
        // 则有dp[i] = (i-1) * k
        // 剩下i-1个数[1:j-1]和[j+1:i]的错位排列有两种方法：
        //  --(1):被交换到第j个位置的原来的第一个数位置不变，剩下的(i-2)个数错位排列，即dp[i-2]
        //  --(2):被交换到第j个位置的原来的第一个数交换位置，不能再放在第j位，即剩下的(i-1)个数错位排列，也就是dp[i-1]
        // 所以：dp[i] = (i-1) * (dp[i-1] + dp[i-2])

        int dp[3] = {1, 0, 1};
        for (int i = 3; i <= n; ++i)
        {
            dp[i % 3] = mulMod(i - 1, dp[(i - 1) % 3] + dp[(i - 2) % 3]);
        }
        return dp[n % 3];
    }

private:
    int mulMod(int a, int b)
    {
        const int m = 1e9 + 7;
        int res = 0;
        // a %= m;
        b %= m;
        while (b)
        {
            if (b & 1)
            {
                res = (res + a) % m;
            }
            a = (a + a) % m;
            b >>= 1;
        }
        return res;
    }
};

class Solution2
{
public:
    int findDerangement(int n)
    {
        const int m = 1e9 + 7;
        int dp[3] = {1, 0, 1};
        for (long long i = 3; i <= n; ++i)
        {
            dp[i % 3] = static_cast<int>((i - 1) * (dp[(i - 1) % 3] + dp[(i - 2) % 3]) % m);
        }
        return dp[n % 3];
    }
};

class Solution3
{
public:
    int findDerangement(int n)
    {
        long long mul = 1, sum = 0, mod = 1e9 + 7;
        for (long long i = n; i >= 0; --i)
        {
            sum = (sum + mod + mul * (i % 2 == 0 ? 1 : -1)) % mod;
            mul = (mul * i) % mod;
        }
        return static_cast<int>(sum);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
