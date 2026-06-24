#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

class Solution
{
public:
    int zigZagArrays(int n, int l, int r)
    {
        constexpr int MOD = 1'000'000'007;
        int k = r - l + 1;  // 值域[l,r]等价于[0,r-l],值域中共有k=r-l+1个整数

        // f0[i][j]:第i个数为i，且第i-1个数和第i个数是「递增」的情况下，包含i个数的锯齿形数组个数
        // f0[i][j] = f1[i-1][0] + f1[i-1][1] + ... + f1[i-1][j-1]
        std::vector<int> f0(k, 1);
        // f1[i][j]:第i个数为i,且第i-1个数和第i个数是「递减」的情况下，包含i个数的锯齿形数组个数
        // f1[i][j] = f0[i-1][j+1] + f0[i-1][j+2] + ... + f0[i-1][r-l]
        std::vector<int> f1(k, 1);

        // s[i][j] = f[i][0] + f[i][1] + ... + f[i][j-1]
        std::vector<long long> s0(k + 1), s1(k + 1);

        for (int i = 2; i <= n; ++i)
        {
            for (int j = 0; j < k; ++j)
            {
                s0[j + 1] = s0[j] + f0[j];
                s1[j + 1] = s1[j] + f1[j];
            }
            for (int j = 0; j < k; ++j)
            {
                f0[j] = s1[j] % MOD;
                f1[j] = (s0[k] - s0[j + 1]) % MOD;
            }
        }

        long long res0 = std::reduce(f0.begin(), f0.end(), 0LL);
        long long res1 = std::reduce(f1.begin(), f1.end(), 0LL);
        return (res0 + res1) % MOD;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}