#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include <algorithm>
#include <numeric>

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

class Solution2
{
public:
    int minimumCost(int n, std::vector<std::vector<int>> &connections)
    {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        rank.resize(n, 0);

        std::sort(connections.begin(), connections.end(),
                  [](const std::vector<int> &lhs, const std::vector<int> &rhs) -> bool {
                      return lhs[2] < rhs[2];
        });

        int ans = 0;
        for (const auto &e : connections)
        {
            if (unite(e[0] - 1, e[1] - 1))
            {
                ans += e[2];
            }
        }

        int root = find(0);
        for (int i = 1; i < n; ++i)
        {
            if (find(i) != root)
                return -1;
        }
        return ans;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;

    int find(int x)
    {
        if (x == parent[x]) return x;
        else return parent[x] = find(parent[x]);
    }

    /** 返回true表示合并成功，返回false表示x,y已经在同一个集合中，合并失败 */
    bool unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y])
        {
            parent[x] = y;
        }
        else
        {
            parent[y] = x;
            if (rank[x] == rank[y])
                ++rank[x];
        }
        return true;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> connections = {{1,2,5},{1,3,6},{2,3,1}};
    int ans = solution.minimumCost(3, connections);
    std::cout << ans << std::endl;
    return 0;
}