#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    double frogPosition(int n, std::vector<std::vector<int>> &edges, int t, int target_)
    {
        target = target_;
        maxTime = t;
        adjList = std::vector<std::vector<int>>(n + 1);
        for (const auto &edge : edges)
        {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
        visited = std::vector<bool>(n + 1, false);
        return dfs(1, 1.0, 0);
    }

private:
    std::vector<std::vector<int>> adjList;
    std::vector<bool> visited;
    int target;
    int maxTime;

    double dfs(int cur, double p, int curT)
    {
        int unvisited = cur == 1 ? adjList[1].size() : adjList[cur].size() - 1;
        visited[cur] = true;
        if (cur == target && (unvisited == 0 || curT == maxTime))
        {
            return p;
        }
        if (curT == maxTime || unvisited == 0)
        {
            return 0.0;
        }
        p /= unvisited;
        for (int neighbor : adjList[cur])
        {
            if (!visited[neighbor])
            {
                double res = dfs(neighbor, p, curT + 1);
                if (res > 0)
                {
                    return res;
                }
            }
        }
        return 0.0;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> edges = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}};
    double ans = solution.frogPosition(7, edges, 2, 4);
    std::cout << ans << std::endl;
    return 0;
}