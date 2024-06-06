#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class Solution
{
public:
    std::vector<int> distanceToCycle(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> g(n);
        std::vector<int> degree(n);
        for (const auto& e : edges)
        {
            int a = e[0], b = e[1];
            g[a].push_back(b);
            g[b].push_back(a);
            ++degree[a];
            ++degree[b];
        }

        std::queue<int> q;
        for (int x = 0; x < n; ++x)
        {
            if (degree[x] == 1)
                q.push(x);
        }
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int y : g[x])
            {
                if (--degree[y] == 1)
                    q.push(y);
            }
        }

        std::vector<int> ans(n, 0);
        std::function<void(int, int)> dfs = [&](int x, int fa) {
            ans[x] = ans[fa] + 1;
            for (int y : g[x])
            {
                if (y != fa)
                    dfs(y, x);
            }
        };
        for (int x = 0; x < n; ++x)
        {
            // 环中节点的度为2
            if (degree[x] != 2)
                continue;

            for (int y : g[x])
            {
                if (degree[y] != 2)
                    dfs(y, x);
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
