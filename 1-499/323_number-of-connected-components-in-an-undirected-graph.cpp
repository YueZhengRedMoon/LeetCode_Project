#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_set>

class Solution
{
public:
    int countComponents(int n, std::vector<std::vector<int>> &edges)
    {
        // 初始化并查集
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        rank.resize(n, 0);

        for (const std::vector<int> &edge : edges)
        {
            unite(edge[0], edge[1]);
        }

        std::unordered_set<int> components;
        for (int i = 0; i < n; ++i)
        {
            int component = find(i);
            components.emplace(component);
        }

        return components.size();
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;

    int find(int x)
    {
        if (x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x != y)
        {
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
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
