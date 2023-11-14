#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    int findTheCity(int n, std::vector<std::vector<int>> &edges, int distanceThreshold)
    {
        const int inf = 0x3f3f3f3f;
        std::vector<std::vector<int>> dis(n, std::vector<int>(n, inf)); // 邻接矩阵

        // 建图
        for (const std::vector<int> &edge : edges)
        {
            int from = edge[0], to = edge[1], weight = edge[2];
            dis[from][to] = weight;
            dis[to][from] = weight;
        }
        for (int i = 0; i < n; ++i)
            dis[i][i] = 0;

        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }

        int ans = inf, minCnt = inf;
        for (int i = n - 1; i >= 0; --i)
        {
            int cnt = std::count_if(dis[i].begin(), dis[i].end(),
                                    [distanceThreshold](int d) -> bool {return 0 < d && d <= distanceThreshold;});
            if (cnt < minCnt)
            {
                minCnt = cnt;
                ans = i;
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
