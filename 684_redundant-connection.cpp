#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>> &edges)
    {
        size = edges.size() + 1;
        parent.resize(size);
        rank.resize(size);
        init();

        for (const auto& edge : edges)
        {
            if (!same(edge[0], edge[1]))
            {
                unite(edge[0], edge[1]);
            }
            else
            {
                return edge;
            }
        }

        return {};
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
    int size;

    /** 初始化并查集 */
    void init()
    {
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    /** 并查集里寻根的过程 */
    int find(int u)
    {
        return u == parent[u] ? u : parent[u] = find(parent[u]);
    }

    /** 将u和v所属的集合合并 */
    void unite(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v) return;
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

    /** 判断u和v是否属于同一个集合 */
    bool same(int u, int v)
    {
        return find(u) == find(v);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
