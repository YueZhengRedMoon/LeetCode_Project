#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    std::vector<int> countPairsOfConnectableServers(std::vector<std::vector<int>>& edges, int signalSpeed)
    {
        int n = edges.size() + 1;
        std::vector<std::vector<std::pair<int, int>>> g(n);
        for (const auto& e : edges)
        {
            int a = e[0], b = e[1], w = e[2];
            g[a].emplace_back(b, w);
            g[b].emplace_back(a, w);
        }

        std::function<int(int, int, int)> dfs = [&](int x, int fa, int dis) -> int {
            int res = (dis % signalSpeed) == 0;
            for (auto [y, w] : g[x])
            {
                if (y != fa)
                {
                    res += dfs(y, x, dis + w);
                }
            }
            return res;
        };

        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i)
        {
            int sum = 0;
            std::vector<int> cnt;
            cnt.reserve(g[i].size());
            for (auto [x, w] : g[i])
            {
                int res = dfs(x, i, w);
                cnt.push_back(res);
                sum += res;
            }

            for (int c : cnt)
            {
                ans[i] += c * (sum - c);
            }
            ans[i] /= 2;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
