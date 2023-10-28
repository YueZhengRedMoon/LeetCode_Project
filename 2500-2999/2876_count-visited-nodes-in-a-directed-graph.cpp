#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<int> countVisitedNodes(std::vector<int> &edges)
    {
        int n = edges.size();
        std::vector<int> ans(n, 0);

        // 每个节点的出度都为1
        // 统计每个节点的入度
        std::vector<int> inDeg(n, 0);
        for (int v : edges)
        {
            ++inDeg[v];
        }

        // 拓扑排序，找到环
        std::vector<int> zeroInDegNodes; // 未进行拓扑排序时，入度为0的节点
        std::queue<int> queue;
        for (int v = 0; v < n; ++v)
        {
            if (inDeg[v] == 0)
            {
                queue.push(v);
                zeroInDegNodes.push_back(v);
            }
        }
        int nodeNotInLoop = 0;  // 不在环中的节点数
        while (!queue.empty())
        {
            int u = queue.front();
            queue.pop();
            int v = edges[u];   // u->v
            if (--inDeg[v] == 0)
                queue.push(v);
            ++nodeNotInLoop;
            ans[u] = -1;    // 将其标记为不在环中
        }
        // 环中所有节点在经过环的长度后遇到已经访问过的节点（即其本身）
        int start;
        std::function<int(int, int)> dfs1 = [&](int v, int ringLen) -> int {
            if (v == start)   // 已经访问过
                return ringLen;
            return ans[v] = dfs1(edges[v], ringLen + 1);
        };
        for (int v = 0; v < n; ++v)
        {
            if (ans[v] == 0)    // v在尚未处理过的环中
            {
                start = v;
                ans[v] = dfs1(edges[v], 1);
            }
        }

        // 对基环树枝末端的节点进行dfs
        std::function<int(int)> dfs2 = [&](int v) -> int {
            if (ans[v] > 0)
                return ans[v];

            return ans[v] = 1 + dfs2(edges[v]);
        };
        for (int v : zeroInDegNodes)
        {
            dfs2(v);
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> edges = {6,3,6,1,0,8,0,6,6};
    std::vector<int> ans = solution.countVisitedNodes(edges);
    debug::printVector(ans);
    return 0;
}
