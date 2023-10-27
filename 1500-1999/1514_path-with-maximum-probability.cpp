#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include "../debug.h"

class Solution
{
public:
    using Pair = std::pair<double, int>;

    double maxProbability(int n, std::vector<std::vector<int>> &edges, std::vector<double> &succProb,
                          int startNode, int endNode)
    {
        // 建图
        int edgeCount = edges.size();
        std::vector<std::forward_list<Pair>> graph(n);
        for (int i = 0; i < edgeCount; ++i)
        {
            graph[edges[i][0]].emplace_front(succProb[i], edges[i][1]);
            graph[edges[i][1]].emplace_front(succProb[i], edges[i][0]);
        }

        // 由于求的是最大概率，相当于最长路径，所以使用大顶堆
        std::priority_queue<Pair, std::vector<Pair>, std::less<>> queue;

        // prob[i]:从起点到i的最大成功概率
        std::vector<double> probs(n, 0);
        probs[startNode] = 1.0;
        queue.emplace(1.0, startNode);

        while (!queue.empty())
        {
            auto [prob, node] = queue.top();
            queue.pop();

            if (probs[node] > prob)
                continue;

            for (auto [successProb, neighbor] : graph[node])
            {
                double reachProb = prob * successProb;
                if (reachProb > probs[neighbor])
                {
                    probs[neighbor] = reachProb;
                    queue.emplace(reachProb, neighbor);
                }
            }
        }

        return probs[endNode];
    }
};

int main()
{
    Solution solution;
    int n = 3;
    std::vector<std::vector<int>> edges = {{0,1},{1,2},{0,2}};
    std::vector<double> succProb = {0.5,0.5,0.2};
    double ans = solution.maxProbability(n, edges, succProb, 0, 2);
    logObj(ans);
    return 0;
}
