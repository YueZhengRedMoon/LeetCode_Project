#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<std::vector<int>> modifiedGraphEdges(int n, std::vector<std::vector<int>> &edges,
                                                     int source, int destination, int target)
    {
        std::vector<std::vector<std::pair<int, int>>> g(n);
        // 建图，同时记录边的编号
        for (int i = 0; i < edges.size(); ++i)
        {
            int x = edges[i][0], y = edges[i][1];
            g[x].emplace_back(y, i);
            g[y].emplace_back(x, i);
        }

        std::vector<std::vector<int>> dis(n, std::vector<int>(2, 0x3f3f3f3f));
        std::vector<bool> visited(n);
        int delta;
        dis[source][0] = dis[source][1] = 0;
        auto dijkstra = [&](int k)  // k表示第一次/第二次
        {
            std::fill(visited.begin(), visited.end(), false);
            while (true)
            {
                int x = -1;
                for (int i = 0; i < n; ++i)
                {
                    if (!visited[i] && (x < 0 || dis[i][k] < dis[x][k]))
                    {
                        x = i;
                    }
                }
                if (x == destination)   // 起点source到终点destination的最短路已经确定
                {
                    return;
                }
                visited[x] = true;
                // 遍历x的所有出边，更新最短路
                for (auto [y, eid] : g[x])
                {
                    int wt = edges[eid][2];
                    if (wt == -1)
                    {
                        wt = 1;
                    }
                    if (k == 1 && edges[eid][2] == -1)
                    {
                        int w = delta + dis[y][0] - dis[x][1];
                        if (w > wt)
                        {
                            edges[eid][2] = wt = w;
                        }
                    }
                    dis[y][k] = std::min(dis[y][k], dis[x][k] + wt);
                }
            }
        };

        dijkstra(0);
        delta = target - dis[destination][0];
        if (delta < 0)
            return {};

        dijkstra(1);
        if (dis[destination][1] < target)
            return {};

        for (auto &e : edges)
            if (e[2] == -1)
                e[2] = 1;

        return edges;
    }
};

class Solution2
{
public:
    std::vector<std::vector<int>> modifiedGraphEdges(int n, std::vector<std::vector<int>> &edges,
                                                     int source, int destination, int target)
    {
        const int inf = 0x3f3f3f3f;
        // 建图，邻接矩阵
        std::vector<std::vector<int>> g(n, std::vector<int>(n, inf));
        for (const auto &e : edges)
        {
            g[e[0]][e[1]] = e[2];
            g[e[1]][e[0]] = e[2];
        }
        std::vector<std::vector<int>> dis(n, std::vector<int>(2, inf));
        std::vector<bool> visited(n);

        // 第一次迭代中，将所有权值为-1的边改为1后，求得的从source到destination的最短路长度
        int disToTarget;
        // 要使最短路的成本变为target，总共需要增加多少边的权值
        int delta;
        auto dijkstra = [&](int k) -> int {
            std::fill(visited.begin(), visited.end(), false);
            dis[k][source] = true;
            while (true)
            {
                int v = -1;
                for (int u = 0; u < n; ++u)
                {
                    if (!visited[u] && (v == -1 || dis[u] < dis[v]))
                    {
                        v = u;
                    }
                }
                if (v == -1)
                    break;
                visited[v] = true;
                for (int u = 0; u < n; ++u)
                {
                    if (g[v][u] == inf) continue;
                    int cost = g[v][u];
                    if (cost == -1)
                    {
                        if (k == 0)
                            cost = 1;
                        else
                        {
                            int newCost = delta + dis[u][0] - dis[v][1];
                            if (newCost > cost)
                            {
                                g[u][v] = g[v][u] = cost = newCost;
                            }
                        }
                    }
                    dis[k][u] = std::min(dis[k][u], dis[k][v] + cost);
                }
            }
            return dis[k][destination];
        };

        disToTarget = dijkstra(0);
        // 最短路长度已经大于target，不可能通过修改边权使最短路变短
        if (disToTarget > target)
            return {};
        delta = target - disToTarget;
        disToTarget = dijkstra(1);
        if (disToTarget != target)
            return {};

        std::vector<std::vector<int>> ans;
        ans.reserve(edges.size());
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (g[i][j] == inf)
                    continue;
                if (g[i][j] == -1)
                    g[i][j] = 1;
                ans.push_back({i, j, g[i][j]});
            }
        }
        std::cout << ans.size() << std::endl;
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> edges{{4,1,-1},{2,0,-1},{0,3,-1},{4,3,-1}};
    int n = 5, source = 0, destination = 1, target = 5;
    std::vector<std::vector<int>> ans = solution.modifiedGraphEdges(n, edges, source, destination, target);
    debug::printVector2D(ans);
    return 0;
}