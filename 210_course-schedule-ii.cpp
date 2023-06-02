#include <iostream>
#include <vector>
#include <queue>
#include <forward_list>
#include <algorithm>

class Solution
{
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> &prerequisites)
    {
        std::vector<int> inDegrees(numCourses, 0);  // 入度
        std::vector<std::forward_list<int>> adjList(numCourses);
        // 构建邻接表，统计每个顶点的入度
        for (const auto &prerequisite : prerequisites)
        {
            adjList[prerequisite[1]].push_front(prerequisite[0]);
            ++inDegrees[prerequisite[0]];
        }

        // 统计入度为0的顶点
        std::queue<int> queue;
        for (int i = 0; i < numCourses; ++i)
        {
            if (inDegrees[i] == 0)
            {
                queue.push(i);
            }
        }

        // 拓扑排序
        std::vector<int> ans;
        ans.reserve(numCourses);
        while (!queue.empty())
        {
            int cur = queue.front();
            queue.pop();
            ans.push_back(cur);
            for (int next : adjList[cur])
            {
                if (--inDegrees[next] == 0)
                {
                    queue.push(next);
                }
            }
        }

        return ans.size() == numCourses ? ans : std::vector<int>();
    }
};

class Solution2
{
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>> &prerequisites)
    {
        adjList.resize(numCourses);
        visited.resize(numCourses, NOT_SEARCH);
        result.reserve(numCourses);

        // 构建有向图邻接表
        for (const auto &prerequisite : prerequisites)
        {
            adjList[prerequisite[1]].push_front(prerequisite[0]);
        }

        // 每次挑选一个未搜索过的顶点开始进行深度优先搜多
        for (int i = 0; i < numCourses && valid; ++i)
        {
            if (visited[i] == NOT_SEARCH)
            {
                dfs(i);
            }
        }

        if (!valid) return {};
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    enum Status {NOT_SEARCH, IN_SEARCH, FINISHED};
    std::vector<std::forward_list<int>> adjList;    // 邻接表存储有向图
    std::vector<Status> visited;                    // 标记每个顶点的状态
    std::vector<int> result;                        // 用数组来模拟栈，下标0为栈底，n-1为栈顶
    bool valid{true};                              // 判断有向图是否有效（无环）

    void dfs(int u)
    {
        // 将顶点标记为“搜索中”
        visited[u] = IN_SEARCH;
        // 搜索其相邻顶点，只要发现有环，立刻停止搜索
        for (int v : adjList[u])
        {
            // 如果未搜索，那么搜索相邻的顶点
            if (visited[v] == NOT_SEARCH)
            {
                dfs(v);
                if (!valid) return;
            }
            // 如果相邻的状态处于“搜索中”，说明遇到了环
            else if (visited[v] == IN_SEARCH)
            {
                valid = false;
                return;
            }
        }
        // 将顶点标记为已完成
        visited[u] = FINISHED;
        // 将顶点入栈
        result.push_back(u);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
