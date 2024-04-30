#include <iostream>
#include <vector>
#include <numeric>
#include "debug.h"

class Solution
{
public:
    int superEggDrop(int k, int n)
    {
        if (n == 1)
            return 1;

        // f[i][j]:可以进行i次操作，有j个鸡蛋，能找到答案的最高楼层是多少？
        // 求出所有的f[t][k],最小的满足f[t][k]>=n的t即为答案
        std::vector<std::vector<int>> f(n + 1, std::vector<int>(k + 1));

        // 只能进行一次操作时，只能确定一层楼的答案
        // f[1][0]初始化为0，没有鸡蛋时，无法确定答案（不确定从1楼扔下去会不会碎）
        std::fill(f[1].begin() + 1, f[1].end(), 1);

        int ans = -1;
        for (int i = 2; i <= n; ++i)
        {
            for (int j = 1; j <= k; ++j)
            {

                // 1:进行一次操作扔一个蛋，可以确定一层楼
                // f[i-1][j-1]:扔出的蛋碎了，剩下i-1次操作扔至多j-1个蛋可以确定答案的楼层数，这一层的下方可以有f[i-1][j-1]层
                // f[i-1][j]:扔出的蛋没碎，剩下i-1次操作扔至多j个蛋可以确定答案的楼层数，这一层的上方可以有f[i-1][j]层
                f[i][j] = 1 + f[i - 1][j - 1] + f[i - 1][j];
            }
            if (f[i][k] >= n)
            {
                ans = i;
                break;
            }
        }

        return ans;
    }
};

namespace TimeLimit
{
    class Solution
    {
    public:
        int superEggDrop(int k, int n)
        {
            // f[i][j]:i层楼、j个蛋，在最坏情况下需要多少次可以测出临界楼层，为无穷大表示无法测出临界楼层
            const int inf = 0x3f3f3f3f;
            std::vector<std::vector<int>> f(n + 1, std::vector<int>(k + 1, inf));

            std::fill(f[0].begin(), f[0].end(), 0); // 没有楼层的情况下，不需要扔蛋
            std::fill(f[1].begin() + 1, f[1].end(), 1); // 在只有一层楼的情况下，只需要扔1次蛋
            for (int i = 2; i <= n; ++i)
            {
                // 在只有1个蛋的情况下，有几层楼就需要扔几次
                f[i][1] = i;
            }

            for (int i = 2; i <= n; ++i)
            {
                for (int j = 2; j <= k; ++j)
                {
                    // 现在有i层楼，j个蛋,枚举从第x层楼开始扔的情况1 <= x <= j
                    for (int x = 1; x <= i; ++x)
                    {
                        // f[x][j-1]:在第x层楼扔，蛋碎了，临界楼层在[0, x-1]中，因为碎了一个蛋，所以只剩j-1个蛋能用
                        // f[i-x][j]:在第x层楼扔，蛋没碎，临界楼层在[x+1, i]中（相当于在[0, i-(x+1)]共i-x层中），因为蛋没碎，所以还有j个蛋可用
                        f[i][j] = std::min(f[i][j], std::max(f[x - 1][j - 1], f[i - x][j]) + 1);
                    }
                }
            }

            debug::printVector2D(f, inf);

            return f[n][k];
        }
    };
}



int main()
{
    Solution solution;
    int n = 10, k = 10;
    int ans = solution.superEggDrop(k, n);
    logObj(ans);
    return 0;
}
