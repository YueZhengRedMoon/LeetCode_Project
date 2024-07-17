#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Solution
{
public:
    using Pair = std::pair<int, int>;

    std::vector<int> minimumTime(int n, std::vector<std::vector<int>>& edges, std::vector<int>& disappear)
    {
        std::vector<std::unordered_map<int, int>> g(n);
        for (const auto& edge : edges)
        {
            int u = edge[0], v = edge[1], w = edge[2];
            auto it = g[u].find(v);
            if (it == g[u].end())
            {
                g[u].emplace(v, w);
                g[v].emplace(u, w);
            }
            else
            {
                if (w < it->second)
                {
                    it->second = w;
                    g[v][u] = w;
                }
            }
        }

        std::vector<int> ans(n, -1);
        ans[0] = 0;
        // first:dis second:node
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> q; // 小顶堆
        q.emplace(0, 0);
        while (!q.empty())
        {
            auto [d, u] = q.top();
            q.pop();
            if (ans[u] != - 1 && d > ans[u])
                continue;

            for (auto [v, w] : g[u])
            {
                int nd = d + w;
                if (nd < disappear[v] && (ans[v] == -1 || nd < ans[v]))
                {
                    ans[v] = nd;
                    q.emplace(nd, v);
                }
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
