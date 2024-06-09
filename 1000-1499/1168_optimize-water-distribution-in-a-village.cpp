#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <numeric>

class Solution
{
public:
    using Pair = std::pair<int, int>;

    int minCostToSupplyWater(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> edgesHeap; // 小顶堆
        std::vector<std::vector<Pair>> g(n + 1);

        for (int i = 0; i < n; ++i)
        {
            // 构建一个虚拟0号节点，假设0号节点已经建了水井，且成本为0
            // 在i号节点(0<i<=n)建水井就等价于搭建一条从0号虚拟节点到i号节点的管道，且管道成本为wells[i-1]
            Pair virtualEdge = {wells[i], i + 1};
            g[0].push_back(virtualEdge);
            edgesHeap.push(virtualEdge);
        }

        for (const auto& p : pipes)
        {
            int h1 = p[0], h2 = p[1], c = p[2];
            g[h1].emplace_back(c, h2);
            g[h2].emplace_back(c, h1);
        }

        int ans = 0;
        std::unordered_set<int> mstSet({0});
        while (mstSet.size() <= n)
        {
            Pair edge = edgesHeap.top();
            edgesHeap.pop();
            int cost = edge.first, nextHouse = edge.second;
            if (mstSet.find(nextHouse) != mstSet.end()) // nextHouse已经在生成树中
                continue;

            mstSet.insert(nextHouse);
            ans += cost;

            for (const Pair& neighborEdge : g[nextHouse])
            {
                if (mstSet.find(neighborEdge.second) == mstSet.end())
                    edgesHeap.push(neighborEdge);
            }
        }

        return ans;
    }
};

struct Edge
{
    int u, v, cost;
    Edge(int x, int y, int c) : u(x), v(y), cost(c) {}
    bool operator>(const Edge& rhs) const { return cost > rhs.cost; }
};

class UnionSet
{
public:
    UnionSet(int n) : parent(n), rank(n)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

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

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

private:
    std::vector<int> parent, rank;
};

class Solution2
{
public:
    int minCostToSupplyWater(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        std::priority_queue<Edge, std::vector<Edge>, std::greater<>> minHeap;
        for (int i = 0; i < n; ++i)
            minHeap.emplace(0, i + 1, wells[i]);
        for (const auto& p : pipes)
            minHeap.emplace(p[0], p[1], p[2]);

        int ans = 0;
        UnionSet unionSet(n + 1);
        while (!minHeap.empty())
        {
            Edge edge = minHeap.top();
            minHeap.pop();
            if (unionSet.same(edge.u, edge.v))
                continue;

            ans += edge.cost;
            unionSet.unite(edge.u, edge.v);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
