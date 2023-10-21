#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>

class UniteSet
{
public:
    UniteSet(int n) : parent(n), rank(n, 0)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        return x == parent[x] ?  x : (parent[x] = find(parent[x]));
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
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

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

class Solution
{
public:
    long long countPairs(int n, std::vector<std::vector<int>> &edges)
    {
        UniteSet uniteSet(n);
        for (const std::vector<int> &edge : edges)
        {
            uniteSet.unite(edge[0], edge[1]);
        }

        std::unordered_map<int, int> components;
        for (int i = 0; i < n; ++i)
        {
            int root = uniteSet.find(i);
            ++components[root];
        }

        long long ans = n * (n - 1ll) / 2ll;
        for (auto it = components.begin(); it != components.end(); ++it)
        {
            long long m = it->second;   // 该连通分量的节点数
            ans -= m * (m - 1ll) / 2ll;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
