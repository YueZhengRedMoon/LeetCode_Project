#include <iostream>
#include <vector>
#include <algorithm>
#include <forward_list>

class Solution
{
public:
    bool leadsToDestination(int n, std::vector<std::vector<int>> &edges, int source, int destination)
    {
        graph.resize(n);
        canLeadsToDes.resize(n, false);
        visited.resize(n, false);

        // 建图
        int edgeNum = edges.size();
        for (int i = 0; i < edgeNum; ++i)
        {
            graph[edges[i][0]].emplace_front(edges[i][1]);
        }

        // 目标终点有出边
        if (!graph[destination].empty())
        {
            return false;
        }

        canLeadsToDes[destination] = true;
        visited[source] = true;
        return dfs(source);
    }

private:
    std::vector<std::forward_list<int>> graph;
    std::vector<bool> canLeadsToDes;
    std::vector<bool> visited;

    bool dfs(int source)
    {
        if (canLeadsToDes[source])
            return true;

        bool transport = false;
        for (int nextSource : graph[source])
        {
            if (visited[nextSource])
            {
                return false;
            }
            else
            {
                visited[nextSource] = true;
                transport = true;
                if (!dfs(nextSource))
                {
                    return false;
                }
                visited[nextSource] = false;
            }
        }

        if (transport)
        {
            return canLeadsToDes[source] = true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
