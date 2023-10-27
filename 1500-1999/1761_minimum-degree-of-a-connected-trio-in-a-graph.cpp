#include <iostream>
#include <vector>
#include <unordered_set>
#include <forward_list>

class Solution
{
public:
    int minTrioDegree(int n, std::vector<std::vector<int>> &edges)
    {
        std::vector<std::vector<bool>> adjMat(n, std::vector<bool>(n, false));  // 邻接矩阵
        std::vector<std::forward_list<int>> adjList(n); // 邻接表，但只记录从编号低的节点到编号高的节点的边
        std::vector<int> degrees(n, 0);
        for (const auto &edge : edges)
        {
            int u = edge[0] - 1, v = edge[1] - 1;
            if (u > v)
                std::swap(u, v);
            adjMat[u][v] = adjMat[v][u] = true;
            adjList[u].emplace_front(v);
            ++degrees[u];
            ++degrees[v];
        }

        const int inf = 0x3f3f3f3f;
        int ans = inf;
        for (int x = 0; x < n - 2; ++x)
        {
            for (int y : adjList[x])
            {
                for (int z : adjList[y])
                {
                    // 找到三元组，统计度数
                    if (adjMat[z][x])
                    {
                        int deg = degrees[x] + degrees[y] + degrees[z] - 6;

                        if (deg < ans)
                        {
                            ans = deg;
                            if (ans == 0)
                                return ans;
                        }
                    }
                }
            }
        }

        return ans == inf ? -1 : ans;
    }
};

class Solution2
{
public:
    int minTrioDegree(int n, std::vector<std::vector<int>> &edges)
    {
        std::vector<std::unordered_set<int>> g(n);  // 原图
        std::vector<std::vector<int>> h(n);         // 定向后的图
        std::vector<int> degree(n, 0);

        for (auto &edge : edges)
        {
            int x = edge[0] - 1, y = edge[1] - 1;
            g[x].insert(y);
            g[y].insert(x);
            ++degree[x];
            ++degree[y];
        }

        for (auto &edge : edges)
        {
            int x = edge[0] - 1, y = edge[1] - 1;
            if (degree[x] < degree[y] || (degree[x] == degree[y] && x < y))
            {
                h[x].push_back(y);
            }
            else
            {
                h[y].push_back(x);
            }
        }

        const int inf = 0x3f3f3f3f;
        int ans = inf;
        for (int i = 0; i < n; ++i)
        {
            for (int j : h[i])
            {
                for (int k : h[j])
                {
                    if (g[i].find(k) != g[i].end())
                    {
                        ans = std::min(ans, degree[i] + degree[j] + degree[k] - 6);
                    }
                }
            }
        }

        return ans == inf ? -1 : ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
