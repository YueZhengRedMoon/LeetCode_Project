#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>> &edges)
    {
        size = edges.size() + 1;
        parent.resize(size);
        rank.resize(size);
        init();

        // 统计入度
        std::vector<int> inDegree(size + 1, 0);
        for (const auto &edge : edges)
        {
            ++inDegree[edge[1]];
        }

        // 寻找入度为2的节点，如果存在入度为2的节点，则需要删除其中的一条边
        std::vector<int> toDelete;
        for (int i = edges.size() - 1; i >= 0; --i)
        {
            if (inDegree[edges[i][1]] == 2)
            {
                toDelete.push_back(i);
            }
        }

        if (!toDelete.empty())
        {
            if (isTreeAfterRemoveEdge(edges, toDelete[0]))
            {
                return edges[toDelete[0]];
            }
            else
            {
                return edges[toDelete[1]];
            }
        }

        // 不存在入度为2的顶点，此时构成有向环
        init();
        for (const auto &edge : edges)
        {
            if (same(edge[0], edge[1]))
            {
                return edge;
            }
            else
            {
                unite(edge[0], edge[1]);
            }
        }

        return {};
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
    int size;

    void init()
    {
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int u)
    {
        return u == parent[u] ? u : parent[u] = find(parent[u]);
    }

    void unite(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
        {
            return;
        }
        if (rank[u] < rank[v])
        {
            parent[u] = v;
        }
        else
        {
            parent[v] = u;
            if (rank[u] == rank[v])
            {
                ++rank[u];
            }
        }
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    /** 判断删一条边之后是不是树 */
    bool isTreeAfterRemoveEdge(const std::vector<std::vector<int>>& edges, int deleteEdge)
    {
        init();
        for (int i = 0; i < edges.size(); ++i)
        {
            if (i != deleteEdge)
            {
                if (same(edges[i][0], edges[i][1]))
                {
                    return false;
                }
                else
                {
                    unite(edges[i][0], edges[i][1]);
                }
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}