#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites)
    {
        std::vector<int> inDegrees(numCourses, 0);  // 入度
        std::vector<std::vector<int>> adjList(numCourses);
        // 构建邻接表，统计每个顶点的入度
        for (const auto &prerequisite : prerequisites)
        {
            adjList[prerequisite[1]].push_back(prerequisite[0]);
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
        int learned = 0;    // 已学的课程
        while (!queue.empty())
        {
            int cur = queue.front();
            queue.pop();
            ++learned;
            for (int next : adjList[cur])
            {
                if (--inDegrees[next] == 0)
                {
                    queue.push(next);
                }
            }
        }

        return learned == numCourses;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
