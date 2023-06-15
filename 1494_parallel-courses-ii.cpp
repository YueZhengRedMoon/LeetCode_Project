#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include <limits>

/** 错误 */
class Solution
{
public:
    int minNumberOfSemesters(int n, std::vector<std::vector<int>> &relations, int k)
    {
        std::vector<int> inDegrees(n + 1, 0);
        std::vector<int> outDegrees(n + 1, 0);
        std::vector<std::forward_list<int>> graph(n + 1);
        std::vector<std::forward_list<int>> reverseGraph(n + 1);

        for (const auto &relation : relations)
        {
            int x = relation[0], y = relation[1];
            ++inDegrees[y];
            ++outDegrees[x];
            graph[x].push_front(y);
            reverseGraph[y].push_front(x);
        }

        for (int i = 1; i <= n; ++i)
        {
            if (outDegrees[i] == 0)
            {
                reverseGraph[0].push_front(i);
            }
        }

        std::vector<int> dis(n + 1, std::numeric_limits<int>::max());
        std::queue<int> queue;
        queue.push(0);
        dis[0] = 0;
        while (!queue.empty())
        {
            int y = queue.front();
            queue.pop();
            for (int x : reverseGraph[y])
            {
                if (dis[y] + 1 < dis[x])
                {
                    dis[x] = dis[y] + 1;
                    queue.push(x);
                }
            }
        }

        // first是距离0号顶点的距离, second是顶点编号
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::less<>> maxHeap;
        for (int i = 1; i <= n; ++i)
        {
            if (inDegrees[i] == 0)
            {
                maxHeap.emplace(dis[i], i);
            }
        }

        int ans = 0;
        while (!maxHeap.empty())
        {
            ++ans;
            std::forward_list<int> nextTerm;
            for (int i = 0; i < k && !maxHeap.empty(); ++i)
            {
                auto [_, x] = maxHeap.top();
                maxHeap.pop();
                for (int y : graph[x])
                {
                    if (--inDegrees[y] == 0)
                    {
                        nextTerm.push_front(y);
                    }
                }
            }
            for (int y : nextTerm)
            {
                maxHeap.emplace(dis[y], y);
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    int minNumberOfSemesters(int n, std::vector<std::vector<int>> &relations, int k)
    {
        const int inf = std::numeric_limits<int>::max();
        // dp[i]:完成课程集合i所需要的最少学期数
        std::vector<int> dp(1 << n, inf);
        // need[i]:完成课程集合i的先修课程集合
        std::vector<int> need(1 << n, 0);

        for (const auto &relation : relations)
        {
            need[(1 << (relation[1] - 1))] |= 1 << (relation[0] - 1);
        }

        dp[0] = 0;
        for (int i = 1; i < (1 << n); ++i)
        {
            // i & (i - 1)将i最右边的1置0
            // i & (-i)获取i最右边的1所对应的值
            need[i] = need[i & (i - 1)] | need[i & (-i)];
            if ((need[i] | i) != i)
            {
                // i 中有任意一门课程的前置课程没有完成学习
                continue;
            }
            // 当前学期可以进行学习的课程集合
            int valid = i ^ need[i];
            // 本学期可以学习的课程数不超过k，则可以全部学习，不需要枚举
            if (__builtin_popcount(valid) <= k)
            {
                dp[i] = std::min(dp[i], dp[i ^ valid] + 1);
            }
            // 本学期可以学习的课程数超过k，需要枚举
            else
            {
                for (int sub = valid; sub; sub = (sub - 1) & valid)
                {
                    if (__builtin_popcount(sub) <= k)
                    {
                        dp[i] = std::min(dp[i], dp[i ^ sub] + 1);
                    }
                }
            }
        }

        return dp[(1 << n) - 1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}