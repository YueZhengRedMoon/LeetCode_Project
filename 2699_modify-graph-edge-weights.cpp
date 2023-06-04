#include <iostream>
#include <vector>
#include <algorithm>

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

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}