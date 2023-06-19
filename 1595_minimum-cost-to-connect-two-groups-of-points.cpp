#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int connectTwoGroups(std::vector<std::vector<int>> &cost)
    {
        const int inf = 0x3f3f3f3f;
        int size1 = cost.size(), size2 = cost[0].size(), m = 1 << size2;
        // dp[i][s]:第一组的前i个点与第二组的点集s的最小连通成本
        // 点集s中，第k位为1，表示第k个点在点集中，第k位为0，表示第k个点不在点集中
        // dp1相当于dp[i-1], dp2相当于dp[i]
        std::vector<int> dp1(m, inf), dp2(m);
        dp1[0] = 0; // 两组点都为空，最小连通成本为0
        for (int i = 1; i <= size1; ++i)
        {
            for (int s = 0; s < m; ++s)
            {
                dp2[s] = inf;
                for (int k = 0; k < size2; ++k)
                {
                    // 如果第k位不在点集s中，则直接跳过
                    if ((s & (1 << k)) == 0)
                        continue;

                    dp2[s] = std::min({
                        dp2[s],
                        // 第二组点集s的第k个点不再与其它点连接
                        dp2[s ^ (1 << k)] + cost[i - 1][k],
                        // 第一组点
                        dp1[s] + cost[i - 1][k],
                        dp1[s ^ (1 << k)] + cost[i - 1][k]});
                }
            }
            dp1.swap(dp2);
        }

        return dp1[m - 1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}