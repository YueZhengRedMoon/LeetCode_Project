#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>

class Solution
{
public:
    int minimumSemesters(int n, std::vector<std::vector<int>> &relations)
    {
        std::vector<std::forward_list<int>> graph(n + 1);
        std::vector<int> inDegree(n + 1, 0);

        for (const std::vector<int> &relation : relations)
        {
            graph[relation[0]].emplace_front(relation[1]);
            ++inDegree[relation[1]];
        }

        int learned = 0, ans = 0;
        std::queue<int> curTerm;
        for (int i = 1; i <= n; ++i)
        {
            if (inDegree[i] == 0)
            {
                curTerm.push(i);
            }
        }


        while (!curTerm.empty())
        {
            ++ans;
            std::queue<int> nextTerm;

            while (!curTerm.empty())
            {
                int course = curTerm.front();
                curTerm.pop();
                ++learned;

                for (int nextCourse : graph[course])
                {
                    if (--inDegree[nextCourse] == 0)
                    {
                        nextTerm.push(nextCourse);
                    }
                }
            }

            std::swap(curTerm, nextTerm);
        }

        return learned == n ? ans : -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
