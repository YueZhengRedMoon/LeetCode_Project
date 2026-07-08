#include <iostream>
#include <vector>

constexpr int MOD = 1'000'000'007;
constexpr int MAX_N = 100'001;
int pow10[MAX_N];   // pow10[i] = 10^i % MOD

// 预处理10的幂
int init = [](){
    pow10[0] = 1;
    for (int i = 1; i < MAX_N; ++i)
    {
        pow10[i] = pow10[i - 1] * 10LL % MOD;
    }
    return 0;
}();

class Solution
{
public:
    std::vector<int> sumAndMultiply(std::string s, std::vector<std::vector<int>>& queries)
    {
        int n = s.size();
        // sumD[i]:s[0, i)的所有数字的和
        // preNum[i]:s[0, i)中连接所有非零数字后的x
        // sumNonZero[i]:s[0, i)中的非零数字个数
        std::vector<int> sumD(n + 1), preNum(n + 1), sumNonZero(n + 1);
        for (int i = 0; i < n; ++i)
        {
            int d = s[i] - '0';
            sumD[i + 1] = sumD[i] + d;  // s的前缀和
            preNum[i + 1] = d > 0 ? (preNum[i] * 10LL + d) % MOD : preNum[i];
            sumNonZero[i + 1] = sumNonZero[i] + (d > 0);
        }

        int m = queries.size();
        std::vector<int> ans(m);
        for (int i = 0; i < m; ++i)
        {
            int l = queries[i][0], r = queries[i][1] + 1;
            int length = sumNonZero[r] - sumNonZero[l];
            long long x = preNum[r] - (long long) preNum[l] * pow10[length] % MOD + MOD;    // +MOD保证结果非负
            ans[i] = x * (sumD[r] - sumD[l]) % MOD;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}