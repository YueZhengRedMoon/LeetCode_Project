#include <iostream>
#include <vector>
#include <numeric>
#include <tuple>
#include <algorithm>

class Solution
{
public:
    using tuple3 = std::tuple<int, int, int>;

    int minCostConnectPoints(std::vector<std::vector<int>> &points)
    {
        int n = points.size();
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        rank.resize(n, 0);
        std::vector<tuple3> edges;
        edges.reserve(n * (n - 1) / 2);

        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                edges.emplace_back(i, j, std::abs(points[i][0] - points[j][0]) + std::abs(points[i][1] - points[j][1]));
            }
        }

        std::sort(edges.begin(), edges.end(), [](const tuple3 &lhs, const tuple3 &rhs) {
            return std::get<2>(lhs) < std::get<2>(rhs);
        });

        int ans = 0;
        for (auto [x, y, cost] : edges)
        {
            if (same(x, y))
                continue;

            ans += cost;
            unite(x, y);
        }

        return ans;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;

    int find(int x)
    {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    int same(int x, int y)
    {
        return find(x) == find(y);
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
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
