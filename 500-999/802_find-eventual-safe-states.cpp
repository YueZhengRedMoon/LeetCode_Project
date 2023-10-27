#include <iostream>
#include <vector>

class Solution
{
public:
    enum Status
    {
        NOT_SEARCH,
        UNSAFE,
        SAFE
    };

    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>> &graph)
    {
        int n = graph.size();
        status.resize(n, NOT_SEARCH);
        for (int i = 0; i < n; ++i)
        {
            if (status[i] == NOT_SEARCH)
                dfs(graph, i);
        }
        std::vector<int> ans;
        for (int i = 0; i < n; ++i)
        {
            if (status[i] == SAFE)
                ans.push_back(i);
        }
        return ans;
    }

private:
    std::vector<Status> status;

    Status dfs(std::vector<std::vector<int>> &graph, int u)
    {
        status[u] = UNSAFE;
        for (const int &v : graph[u])
        {
            if (status[v] == NOT_SEARCH)
            {
                Status res = dfs(graph, v);
                if (res == UNSAFE)
                    return UNSAFE;
            }
            else if (status[v] == UNSAFE)
            {
                return UNSAFE;
            }
        }
        return status[u] = SAFE;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
