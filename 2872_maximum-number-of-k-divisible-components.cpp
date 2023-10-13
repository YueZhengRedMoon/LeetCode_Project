#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <unordered_set>
#include "debug.h"

class Solution
{
public:
    int maxKDivisibleComponents(int n, std::vector<std::vector<int>> &edges, std::vector<int> &values, int k)
    {
        std::vector<std::unordered_set<int>> graph(n);
        std::vector<bool> isDivided(n, false);
        std::vector<int> deg(n, 0);
        for (const std::vector<int> &edge : edges)
        {
            int u = edge[0], v = edge[1];
            graph[u].insert(v);
            graph[v].insert(u);
            ++deg[u];
            ++deg[v];
        }

        std::vector<long long> compVal(n, 0); // compVal[v]:以为根节点的子树的连通块的值
        std::queue<int> queue;
        for (int v = 0; v < n; ++v)
        {
            if (deg[v] == 1)
            {
                queue.push(v);
            }
            compVal[v] = values[v];
        }

        int ans = 0;
        while (!queue.empty())
        {
            int v = queue.front();
            queue.pop();

            if (graph[v].empty())
            {
                if (compVal[v] % k == 0)
                    ++ans;
                else
                    return 0;
            }
            else
            {
                int par = *graph[v].begin();
                graph[par].erase(v);
                if (--deg[par] == 1)
                    queue.push(par);

                if (compVal[v] % k == 0)
                    ++ans;
                else
                    compVal[par] += compVal[v];
            }
        }

        return std::max(ans, 1);
    }
};

class Solution2
{
public:
    int maxKDivisibleComponents(int n, std::vector<std::vector<int>> &edges, std::vector<int> &values, int k)
    {
        int ans = 0;
        std::vector<std::vector<int>> graph(n);
        for (const std::vector<int> &edge : edges)
        {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        std::function<long long(int, int)> dfs = [&](int cur, int pre) -> long long {
            long long sum = values[cur];
            for (int next : graph[cur])
            {
                if (next != pre)
                    sum += dfs(next, cur);
            }
            ans += (sum % k == 0);
            return sum;
        };
        dfs(0, -1);

        return ans;
    }
};

int main()
{
    Solution solution;
    int n = 5;
    std::vector<std::vector<int>> edges = {{0,2},{1,2},{1,3},{2,4}};
    std::vector<int> values = {1,8,1,4,4};
    int k = 6;
    int ans = solution.maxKDivisibleComponents(n, edges, values, k);
    logObj(ans);
    return 0;
}
