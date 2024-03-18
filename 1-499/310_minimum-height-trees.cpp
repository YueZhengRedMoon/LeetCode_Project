#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    std::vector<int> findMinHeightTrees(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> g(n);
        std::vector<int> degree(n);
        for (const std::vector<int>& e : edges)
        {
            // 建图
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);

            // 统计节点的度
            ++degree[e[0]];
            ++degree[e[1]];
        }

        // 统计所有度为1的节点，准备拓扑排序
        std::queue<int> queue;
        for (int i = 0; i < n; ++i)
        {
            if (degree[i] == 1)
            {
                queue.push(i);
            }
        }

        // 拓扑排序
        std::vector<int> dis(n);    // dis[i]:节点i从外到里的深度
        int maxDis = 0; // 从外到里的最大深度
        while (!queue.empty())
        {
            int x = queue.front();
            queue.pop();
            for (int y : g[x])
            {
                if (--degree[y] == 1)
                {
                    dis[y] = dis[x] + 1;
                    if (dis[y] > maxDis)
                        maxDis = dis[y];
                    queue.push(y);
                }
            }
        }

        std::vector<int> ans;
        for (int i = 0; i < n; ++i)
        {
            if (dis[i] == maxDis)
                ans.push_back(i);
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
