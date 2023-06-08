#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>

class Solution
{
public:
    int minimumCost(int n, std::vector<std::vector<int>> &connections)
    {
        const int inf = 0x3f3f3f3f;
        // first是顶点编号，second是权值
        std::vector<std::forward_list<std::pair<int, int>>> graph(n);
        for (const auto &e : connections)
        {
            int u = e[0] - 1, v = e[1] - 1;
            graph[u].emplace_front(v, e[2]);
            graph[v].emplace_front(u, e[2]);
        }

        int count = 0; // 加入到生产树中的顶点数
        int ans = 0;

        std::vector<bool> visited(n, false);
        // 所有顶点到生产树的最小的权值
        std::vector<int> minCost(n, inf);
        minCost[0] = 0;

        // 队列中first是顶点到生成树的成本，second是顶点的编号
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;
        queue.emplace(0, 0);

        while (count < n && !queue.empty())
        {
            auto [cost, u] = queue.top();
            queue.pop();
            if (visited[u] || cost > minCost[u])
                continue;
            visited[u] = true;
            ++count;
            ans += cost;
            for (const auto &e : graph[u])
            {
                int v = e.first;
                cost = e.second;
                if (!visited[v] && cost < minCost[v])
                {
                    queue.emplace(cost, v);
                    minCost[v] = cost;
                }
            }
        }

        return count < n ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}