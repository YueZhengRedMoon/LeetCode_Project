#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>

class Solution
{
public:
    int minimumTime(int n, std::vector<std::vector<int>> &relations, std::vector<int> &time)
    {
        std::vector<int> inDegree(n, 0);
        std::vector<std::forward_list<int>> subsequent(n + 1);  // 每门课的后继课程
        // 建图
        for (const std::vector<int> &relation : relations)
        {
            int prevCourse = relation[0] - 1, nextCourse = relation[1] - 1;
            subsequent[prevCourse].emplace_front(nextCourse);
            ++inDegree[nextCourse];
        }

        std::queue<int> queue;
        for (int i = 0; i < n; ++i)
        {
            if (inDegree[i] == 0)
                queue.push(i);
        }

        std::vector<int> earliest(n, 0);                  // 每项工作的最早完成时间
        int ans = 0;
        while (!queue.empty())
        {
            int course = queue.front();
            queue.pop();
            earliest[course] += time[course];
            if (earliest[course] > ans)
                ans = earliest[course];

            for (int nextCourse : subsequent[course])
            {
                if (earliest[course] > earliest[nextCourse])
                    earliest[nextCourse] = earliest[course];
                if (--inDegree[nextCourse] == 0)
                {
                    queue.push(nextCourse);
                }
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}