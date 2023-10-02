#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int countCompleteComponents(int n, std::vector<std::vector<int>> &edges)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            rank[i] = 0;
            degree[i] = 0;
        }

        for (const auto &edge : edges)
        {
            unite(edge[0], edge[1]);
            ++degree[edge[0]];
            ++degree[edge[1]];
        }

        std::unordered_map<int, std::pair<int, bool>> components;
        for (int i = 0; i < n; ++i)
        {
            int x = find(i);
            auto &component = components[x];
            ++component.first;
            component.second = true;
        }

        for (int i = 0; i < n; ++i)
        {
            int par = parent[i];
            auto &component = components[par];
            if (degree[i] + 1 != component.first)
            {
                component.second = false;
            }
        }

        return std::count_if(components.begin(), components.end(),
                             [](const std::pair<int, std::pair<int, bool>> &component){
                                 return component.second.second;
                             });
    }

private:
    int parent[50];
    int rank[50];
    int degree[50];

    int find(int x)
    {
        if (parent[x] == x)
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
        if (x == y) return;
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
