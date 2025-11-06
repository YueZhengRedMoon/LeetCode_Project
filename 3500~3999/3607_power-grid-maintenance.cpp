#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <queue>

class UnionSet
{
public:
    UnionSet(int n)
            : parent(n)
            , rank(n)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        else
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

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

class Solution
{
public:
    std::vector<int> processQueries(int c, std::vector<std::vector<int>>& connections, std::vector<std::vector<int>>& queries)
    {
        UnionSet unionSet(c);
        for (const std::vector<int>& connection : connections)
        {
            int u = connection[0] - 1, v = connection[1] - 1;
            unionSet.unite(u, v);
        }

        std::unordered_map<int, std::priority_queue<int, std::vector<int>, std::greater<>>> group;
        for (int i = 0; i < c; ++i)
        {
            int x = unionSet.find(i);
            group[x].push(i);
        }

        std::vector<bool> isOnline(c, true);
        std::vector<int> ans;
        for (const std::vector<int>& q : queries)
        {
            int type = q[0], x = q[1] - 1;
            if (type == 1)
            {
                if (isOnline[x])
                {
                    ans.push_back(x + 1);
                    continue;
                }

                int px = unionSet.find(x);
                while (!group[px].empty())
                {
                    if (isOnline[group[px].top()])
                    {
                        break;
                    }
                    else
                    {
                        group[px].pop();
                        continue;
                    }
                }

                if (group[px].empty())
                {
                    ans.push_back(-1);
                }
                else
                {
                    ans.push_back(group[px].top() + 1);
                }
            }
            else    // type == 2
            {
                isOnline[x] = false;
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