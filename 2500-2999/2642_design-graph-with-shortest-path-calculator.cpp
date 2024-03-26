#include <iostream>
#include <vector>

class Graph
{
public:
    Graph(int n, std::vector<std::vector<int>>& edges)
    : dis(n, std::vector<int>(n, inf))
    {
        for (const std::vector<int>& edge : edges)
        {
            int from = edge[0], to = edge[1], edgeCost = edge[2];
            dis[from][to] = edgeCost;
        }

        for (int i = 0; i < n; ++i)
        {
            dis[i][i] = 0;
        }

        // Floyd算法计算最短路
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
    }

    void addEdge(std::vector<int> edge)
    {
        int from = edge[0], to = edge[1], edgeCost = edge[2];
        if (edgeCost < dis[from][to])
        {
            int n = dis.size();
            dis[from][to] = edgeCost;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    dis[i][j] = std::min(dis[i][j], dis[i][from] + edgeCost + dis[to][j]);
                }
            }
        }
    }

    int shortestPath(int node1, int node2)
    {
        return dis[node1][node2] == inf ? -1 : dis[node1][node2];
    }

private:
    const int inf {0x3f3f3f3f};
    std::vector<std::vector<int>> dis;
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
