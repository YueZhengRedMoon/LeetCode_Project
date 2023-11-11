#include <iostream>
#include <vector>
#include <numeric>
#include "debug.h"

class UnionSet
{
public:
    UnionSet(int n) : size(n), count(n), parent(n), rank(n, 0)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        return parent[x] == x ? x : (parent[x] = find(parent[x]));
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
        --count;
    }

    int getCount() const
    {
        return count;
    }

private:
    int size;
    int count;  // 连通分量的数量
    std::vector<int> parent;
    std::vector<int> rank;
};

class Solution
{
public:
    int minSwapsCouples(std::vector<int> &row)
    {
        int rowLen = row.size();
        int n = rowLen / 2;
        UnionSet unionSet(n);
        for (int i = 0; i < rowLen; i += 2)
        {
            unionSet.unite(row[i] / 2, row[i + 1] / 2);
        }
        return n - unionSet.getCount();
    }
};

int main()
{
    Solution solution;
    std::vector<int> row = {2, 0, 5, 4, 3, 1};
    int ans = solution.minSwapsCouples(row);
    logObj(ans);
    return 0;
}
