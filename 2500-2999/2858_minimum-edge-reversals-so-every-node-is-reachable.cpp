#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> minEdgeReversals(int n, std::vector<std::vector<int>> &edges)
    {
        graph.resize(n);
        visited.resize(n, false);
        ans.resize(n, -1);
        for (const std::vector<int> &edge : edges)
        {
            int u = edge[0], v = edge[1];
            graph[u].emplace_back(v, 1);
            graph[v].emplace_back(u, -1);
        }

        ans[0] = dfs(0);
        dp(0);

        return ans;
    }

private:
    // first:邻接节点的编号, second:方向，如果u是当前节点,v是邻接节点，则u->v=1, v->u=-1
    std::vector<std::vector<std::pair<int, int>>> graph;
    std::vector<bool> visited;
    std::vector<int> ans;

    // 从u出发，访问所有未访问的节点需要进行的边翻转次数
    int dfs(int u)
    {
        int reverse = 0;
        visited[u] = true;
        for (auto [v, dir] : graph[u])
        {
            if (!visited[v])
            {
                if (dir == -1)
                    ++reverse;
                reverse += dfs(v);
            }
        }
        return reverse;
    }

    // 换根DP
    void dp(int u)
    {
        for (auto [v, dir] : graph[u])
        {
            if (ans[v] == -1)
            {
                ans[v] = ans[u] + dir;
                dp(v);
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
