#include <iostream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <queue>

constexpr int MAX_N = 500;  // 最多有多少条公交线路

class Solution
{
public:
    using Pair = std::pair<int, int>;

    int numBusesToDestination(std::vector<std::vector<int>>& routes, int source, int target)
    {
        if (source == target)
            return 0;

        int n = routes.size();
        // belongTo[i]:站台i在哪些公交线路上
        std::unordered_map<int, std::bitset<MAX_N>> belongTo;
        for (int i = 0; i < n; ++i)
        {
            for (int x : routes[i])
            {
                belongTo[x].set(i);
            }
        }

        // g[i][j]:线路i到线路j是否可以经过1次换乘到达
        std::vector<std::bitset<MAX_N>> g(n);
        for (int i = 0; i < n; ++i)
        {
            for (int x : routes[i])
            {
                g[i] |= belongTo[x];
            }
        }

        const int INF = 0x3f3f3f3f;
        // dis[i]:从source所在的线路，到线路i最少需要乘坐的公交车数，如果为inf,则表示无法到达
        std::vector<int> dis(n, INF);
        // Dijkstra优先队列，Pair.first:乘坐的公交车数，Pair.second:到达的线路
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
        for (int r = 0; r < n; ++r)
        {
            if (belongTo[source][r])    // source在线路r上
            {
                dis[r] = 1;
                pq.emplace(1, r);
            }
        }

        // Dijkstra算法，求最少乘坐公交车数
        while (!pq.empty())
        {
            auto [d, x] = pq.top();
            pq.pop();
            if (d > dis[x])
                continue;

            ++d;
            for (int y = 0; y < n; ++y)
            {
                if (g[x][y] && d < dis[y])
                {
                    pq.emplace(d, y);
                    dis[y] = d;
                }
            }
        }

        int ans = INF;
        for (int r = 0; r < n; ++r)
        {
            if (belongTo[target][r] && ans > dis[r])
                ans = dis[r];
        }
        return ans == INF ? -1 : ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> routes = {{1, 2, 7}, {3, 6, 7}};
    int source = 1;
    int target = 6;
    int ans = solution.numBusesToDestination(routes, source, target);
    std::cout << ans << std::endl;
    return 0;
}
