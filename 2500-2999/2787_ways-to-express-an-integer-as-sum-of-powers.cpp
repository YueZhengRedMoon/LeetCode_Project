#include <iostream>
#include <vector>

const int MAX_N = 300;
const int MAX_X = 5;

// powersX[x] = {1, 2^x, 3^x, ..., i^x}, 其中i^x <= MAX_N
std::vector<int> powersX[MAX_X + 1];

// 计算x^n
int quickPow(int x, int n)
{
    int res = 1;
    while (n)
    {
        if (n & 1)
            res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

int init = [](){
    powersX[1].reserve(MAX_N);
    for (int i = 1; i <= MAX_N; ++i)
        powersX[1].push_back(i);
    for (int x = 2; x <= MAX_X; ++x)
    {
        powersX[x].push_back(1);    // 1^x = 1
        int i = 2;
        while (true)
        {
            int ix = quickPow(i, x);
            if (ix > MAX_N)
                break;
            powersX[x].push_back(ix);
            ++i;
        }
    }
    return 0;
}();

class Solution
{
public:
    int numberOfWays(int n, int x)
    {
        const int MOD = 1'000'000'007;

        int m = powersX[x].size();
        // f[i][j]: 在powersX[0, j)中能凑出i的方案数
        std::vector<std::vector<int>> f(n + 1, std::vector<int>(m + 1));

        // 在powersX[0, j)中能凑出0的方案数为1，即什么数都不选
        for (int j = 0; j <= m; ++j)
            f[0][j] = 1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                f[i][j] = f[i][j - 1];  // 不选当前数

                // 选当前数
                int y = powersX[x][j - 1];
                if (i >= y)
                    f[i][j] = (f[i][j] + f[i - y][j - 1]) % MOD;
            }
        }

        return f[n][m];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
