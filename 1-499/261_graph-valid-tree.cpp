#include <iostream>
#include <vector>
#include <forward_list>

class Solution
{
public:
    bool validTree(int n, std::vector<std::vector<int>> &edges)
    {
        status.resize(n, NOT_SEARCH);
        adjList.resize(n);
        for (const auto &e : edges)
        {
            adjList[e[0]].push_front(e[1]);
            adjList[e[1]].push_front(e[0]);
        }

        if (dfs(0, -1))
            return false;
        for (int i = 1; i < n; ++i)
        {
            if (status[i] == NOT_SEARCH)
                return false;
        }
        return true;
    }

private:
    enum Status
    {
        NOT_SEARCH,
        SEARCHING,
        FINISHED
    };

    std::vector<std::forward_list<int>> adjList;
    std::vector<Status> status;

    bool dfs(int u, int from)
    {
        status[u] = SEARCHING;
        for (const int &v : adjList[u])
        {
            if (v == from)
                continue;
            if (status[v] == NOT_SEARCH)
            {
                if (dfs(v, u))
                    return true;
            }
            else if (status[v] == SEARCHING)
            {
                return true;
            }
        }
        status[u] = FINISHED;
        return false;
    }
};

class Solution2
{
public:
    bool validTree(int n, std::vector<std::vector<int>> &edges)
    {
        rank.resize(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }

        for (const auto &e : edges)
        {
            if (unite(e[0], e[1]))
                return false;
        }

        int root = find(0);
        for (int i = 1; i < n; ++i)
        {
            if (find(i) != root)
            {
                return false;
            }
        }
        return true;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;

    int find(int x)
    {
        if (parent[x] == x) return x;
        else return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y)
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
            return false;
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}