#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int minCost(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<std::pair<int, int>>> g(n);
        for (const std::vector<int>& e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, 2 * w);
        }

        const int INF = 0x3f3f3f3f;
        std::vector<int> dis(n, INF);
        dis[0] = 0;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.emplace(0, 0);
        while (!pq.empty())
        {
            auto [u, cost] = pq.top();
            pq.pop();

            if (cost > dis[u])
                continue;

            if (u == n - 1)
                return cost;

            for (const auto& [v, w] : g[u])
            {
                if (cost + w < dis[v])
                {
                    dis[v] = cost + w;
                    pq.emplace(v, dis[v]);
                }
            }
        }
        return -1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}