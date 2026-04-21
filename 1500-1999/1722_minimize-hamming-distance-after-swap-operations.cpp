#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>

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
        {
            return x;
        }
        else
        {
            return parent[x] = find(parent[x]);
        }
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
            else    // rank[x] >= rank[y]
            {
                parent[y] = x;
                if (rank[x] == rank[y])
                {
                    ++rank[x];
                }
            }
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

class Solution
{
public:
    int minimumHammingDistance(std::vector<int>& source, std::vector<int>& target, std::vector<std::vector<int>>& allowedSwaps)
    {
        int n = source.size();
        UnionSet unionSet(n);
        for (const std::vector<int>& allowedSwap : allowedSwaps)
        {
            unionSet.unite(allowedSwap[0], allowedSwap[1]);
        }

        std::unordered_map<int, std::vector<int>> group;
        for (int i = 0; i < n; ++i)
        {
            int root = unionSet.find(i);
            group[root].push_back(i);
        }

        int ans = 0;
        for (auto it = group.begin(); it != group.end(); ++it)
        {
            int root = it->first;
            const std::vector<int>& children = it->second;
            std::unordered_map<int, int> counter;
            for (int idx : children)
            {
                ++counter[source[idx]];
            }
            for (int idx : children)
            {
                int t = target[idx];
                if (counter.find(t) == counter.end() || counter[t] == 0)
                {
                    ++ans;
                }
                else
                {
                    --counter[t];
                }
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}