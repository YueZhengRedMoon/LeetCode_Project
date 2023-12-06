#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int minimumTotalPrice(int n, std::vector<std::vector<int>> &edges, std::vector<int> &price,
                          std::vector<std::vector<int>> &trips)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto &edge : edges)
        {
            int a = edge[0], b = edge[1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        std::vector<int> cnt(n);
        for (auto &trip : trips)
        {
            int start = trip[0], end = trip[1];
            std::function<bool(int, int)> dfs = [&](int x, int fa) -> bool {
                if (x == end)
                {
                    ++cnt[x];
                    return true;
                }
                for (int y : graph[x])
                {
                    if (y != fa && dfs(y, x))
                    {
                        ++cnt[x];
                        return true;
                    }
                }
                return false;
            };
            dfs(start, -1);
        }

        std::function<std::pair<int, int>(int, int)> dfs = [&](int x, int fa) -> std::pair<int, int> {
            int notHalve = price[x] * cnt[x];   // x不变
            int halve = notHalve / 2;           // x减半
            for (int y : graph[x])
            {
                if (y != fa)
                {
                    auto [nh, h] = dfs(y, x);
                    notHalve += std::min(nh, h);
                    halve += nh;
                }
            }
            return {notHalve, halve};
        };

        auto [nh, h] = dfs(0, -1);
        return std::min(nh, h);
    }
};

namespace Error
{
    class Solution
    {
    public:
        int minimumTotalPrice(int n, std::vector<std::vector<int>> &edges, std::vector<int> &price,
                              std::vector<std::vector<int>> &trips)
        {
            const int inf = 0x3f3f3f3f;
            std::vector<int> actualPrice(n);
            std::vector<std::vector<int>> graph(n);
            for (const auto &edge : edges)
            {
                int a = edge[0], b = edge[1];
                graph[a].push_back(b);
                graph[b].push_back(a);
            }

            std::function<void(int, int, bool)> cutPrice = [&](int x, int parent, bool cut) {
                actualPrice[x] = (cut ? price[x] / 2 : price[x]);
                for (int y : graph[x])
                {
                    if (y != parent)
                        cutPrice(y, x, !cut);
                }
            };

            std::function<int()> floyd = [&]() -> int {
                std::vector<std::vector<int>> dis(n, std::vector<int>(n, inf));
                for (const auto &edge : edges)
                {
                    int a = edge[0], b = edge[1];
                    dis[a][b] = dis[b][a] = actualPrice[a] + actualPrice[b];
                }
                for (int i = 0; i < n; ++i)
                {
                    dis[i][i] = actualPrice[i];
                }

                for (int k = 0; k < n; ++k)
                {
                    for (int i = 0; i < n; ++i)
                    {
                        for (int j = 0; j < n; ++j)
                        {
                            if (dis[i][k] != inf && dis[k][j] != inf)
                            {
                                int temp = dis[i][k] + dis[k][j] - actualPrice[k];
                                if (temp < dis[i][j])
                                    dis[i][j] = temp;
                            }
                        }
                    }
                }

                int res = 0;
                for (const auto &trip : trips)
                {
                    int start = trip[0], end = trip[1];
                    res += dis[start][end];
                }

                return res;
            };

            cutPrice(0, -1, true);
            int ans = floyd();
            cutPrice(0, -1, false);
            ans = std::min(ans, floyd());

            return ans;
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
