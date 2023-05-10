#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    /** 为了方便，将所有变量从0开始编号
         *  房子的编号为[0, m-1]
         *  颜色的编号为[0, n-1]，如果房子没有涂上色，记为-1
         *  街区的编号为[0, target-1]
         * */

    /** dp(i, j, k):将[0, i]的房子都涂上色，最末尾的第i个房子的颜色为j，并且它属于第k个街区时，需要的最少花费
     *  涂第i个房子时，需要考虑第i-1个房子的情况，设第i-1个房子的颜色为j0
     *  如果house[i] != -1，说明第i个房子已经涂过色了，由于不能重复涂色，则必须有house[i] = j:
     *      dp(i, j, k) = inf，          如果house[i] != -1并且house[i] != j (因为要求的是最小值，inf不会影响结果)
     *  当house[i] = j时，如果j = j0，那么第i-1个房子和第i个房子属于同一个街区：
     *      dp(i, j, k) = dp(i-1, j, k)，如果house[i]=j
     *  如果j != j0，则它们属于不同的街区：
     *      dp(i, j, k) = min dp(i-1, j0, k-1)
     *
     *  如果house[i]=-1，说明需要将第i个房子涂成颜色j，花费为cost[i][j]，如果j = j0:
     *      dp(i, j, k) = dp(i-1, j, k - 1) + cost[i][j]， 如果house[i] = -1
     *  如果j != j0，则状态转移方程为：
     *      dp(i, j, k) = min dp(i - 1, j0, k - 1) + cost[i][j]， 如果house[i] = -1
     *
     *  最终答案即为min dp(m-1, j, target -1) */

    int minCost(std::vector<int> &houses, std::vector<std::vector<int>> &cost, int m, int n, int target)
    {
        // 将颜色从0开始编号，没有被涂色标记为-1
        for (int &c : houses)
        {
            --c;
        }

        std::vector<std::vector<std::vector<int>>> dp(m, std::vector<std::vector<int>>(n, std::vector<int>(target, inf)));

        // 初始化
        if (houses[0] != -1)
        {
            dp[0][houses[0]][0] = 0;
        }
        else
        {
            for (int j = 0; j < n; ++j)
                dp[0][j][0] = cost[0][j];
        }

        // 遍历每一幢房子
        for (int i = 1; i < m; ++i)
        {
            // 遍历每一种颜色
            for (int j = 0; j < n; ++j)
            {
                // 当前房子已经涂过色了，如果涂的色与当前考虑的颜色不一致，则跳过
                if (houses[i] != -1 && houses[i] != j)
                    continue;

                // 枚举街区数
                for (int k = 0; k < target; ++k)
                {
                    // 枚举上一幢房子涂的颜色
                    for (int j0 = 0; j0 < n; ++j0)
                    {
                        // 当前要涂的颜色与上一幢房子颜色相同,这幢房子与上一幢房子属于同一个街区
                        if (j == j0)
                        {
                            dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j][k]);
                        }
                        // 当前要涂的颜色与上一幢房子颜色不同,这幢房子与上一幢房子不属于同一个街区
                        else if (k > 0)
                        {
                            dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j0][k - 1]);
                        }
                    }

                    if (dp[i][j][k] != inf && houses[i] == -1)
                        dp[i][j][k] += cost[i][j];
                }
            }
        }

        int ans = inf;
        for (int j = 0; j < n; ++j)
        {
            ans = std::min(ans, dp[m - 1][j][target - 1]);
        }
        return ans == inf ? -1 : ans;
    }

private:
    static constexpr int inf{std::numeric_limits<int>::max() / 2};
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
