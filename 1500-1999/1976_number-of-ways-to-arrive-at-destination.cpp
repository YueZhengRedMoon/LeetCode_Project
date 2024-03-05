#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>

class Solution
{
public:
    int countPaths(int n, std::vector<std::vector<int>>& roads)
    {
        // 建图
        // g[i][j].first:节点编号，g[i][j].second:边的权值
        std::vector<std::vector<std::pair<int, int>>> g(n);
        for (const auto& road : roads)
        {
            int u = road[0], v = road[1], time = road[2];
            g[u].emplace_back(v, time);
            g[v].emplace_back(u, time);
        }

        // Dijkstra算法求最短路
        const long long inf = std::numeric_limits<long long>::max();
        std::vector<long long> dis(n, inf); // dis[i]:从路口0到路口i的最短时间
        dis[0] = 0;
        std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> minHeap;
        minHeap.emplace(0, 0);
        while (!minHeap.empty())
        {
            auto [d, u] = minHeap.top();
            minHeap.pop();

            if (dis[u] < d)
                continue;

            for (const auto& [v, time] : g[u])
            {
                if (dis[u] + time < dis[v])
                {
                    dis[v] = dis[u] + time;
                    minHeap.emplace(dis[v], v);
                }
            }
        }

        // paths[i]:以最少时间从路口0到路口i的路径数
        std::vector<int> paths(n, -1);
        paths[0] = 1;
        const int MOD = 1e9 + 7;
        std::function<int(int)> dfs = [&](int u) -> int {
            if (paths[u] != -1)
                return paths[u];

            int res = 0;
            for (const auto& [v, time] : g[u])
            {
                if (dis[u] == dis[v] + time)
                {
                    res = (res + dfs(v)) % MOD;
                }
            }

            return paths[u] = res;
        };
        return dfs(n - 1);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
