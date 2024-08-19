#include <iostream>
#include <vector>
#include <functional>

// 记忆化搜索
namespace Solution1
{
    const int MOD = 1'000'000'007;
    const int MAX_N = 100001;
    int memo[MAX_N][2][3];  // 记忆化数组

    class Solution
    {
    public:
        int checkRecord(int n)
        {
            return dfs(n, 0, 0);
        }

    private:
        // dfs(i,j,k):从右往左填，右边填了j(j<2)个A，且右边相邻位置有k(k<3)个连续L的情况下，
        // 继续向左填字母，能构造多少个长为i的字符串
        int dfs(int i, int j, int k)
        {
            if (i == 0)
            {
                // 构造1个空串
                return 1;
            }

            int& res = memo[i][j][k];
            if (res)
                return res;

            // 填P
            res = dfs(i - 1, j, 0);

            // 填A
            if (j == 0)
                res = (res + dfs(i - 1, 1, 0)) % MOD;

            // 填L
            if (k < 2)
                res = (res + dfs(i - 1, j, k + 1)) % MOD;

            return res;
        }
    };
}

// 记忆化搜索转递推
namespace Solution2
{
    const int MOD = 1'000'000'007;
    const int MAX_N = 100001;
    int f[MAX_N][2][3]; // f[i][j][k]:填了j(j<2)个A，且最后有k(k<3)个连续L的情况下，能构造多少个长为i的字符串

    int init = []{
        f[0][0][0] = f[0][0][1] = f[0][0][2] = f[0][1][0] = f[0][1][1] = f[0][1][2] = 1;
        for (int i = 1; i < MAX_N; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    int& res = f[i][j][k];
                    // 填P
                    res = f[i - 1][j][0];
                    // 填A
                    if (j == 0)
                        res = (res + f[i - 1][1][0]) % MOD;
                    // 填L
                    if (k < 2)
                        res = (res + f[i - 1][j][k + 1]) % MOD;
                }
            }
        }
        return 0;
    }();

    class Solution
    {
    public:
        int checkRecord(int n)
        {
            return f[n][0][0];
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
