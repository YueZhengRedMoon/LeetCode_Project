#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include <functional>

class Solution
{
public:
    std::vector<bool> checkIfPrerequisite(int numCourses, std::vector<std::vector<int>> &prerequisites,
                                          std::vector<std::vector<int>> &queries)
    {
        std::vector<std::forward_list<int>> preGraph(numCourses), nextGraph(numCourses);
        std::vector<int> nextInDeg(numCourses, 0);
        for (const std::vector<int> &pre : prerequisites)
        {
            int a = pre[0], b = pre[1];
            preGraph[b].emplace_front(a);
            nextGraph[a].emplace_front(b);
            ++nextInDeg[b];
        }

        std::queue<int> queue;
        for (int i = 0; i < numCourses; ++i)
        {
            if (nextInDeg[i] == 0)
            {
                queue.push(i);
            }
        }

        std::vector<std::vector<bool>> isPre(numCourses, std::vector<bool>(numCourses, false));
        int cur;
        std::function<void(int)> dfs = [&](int pre) -> void
        {
            isPre[pre][cur] = true;

            for (int p : preGraph[pre])
            {
                if (!isPre[p][cur])
                    dfs(p);
            }
        };

        while (!queue.empty())
        {
            cur = queue.front();
            queue.pop();

            dfs(cur);

            for (int next : nextGraph[cur])
            {
                if (--nextInDeg[next] == 0)
                    queue.push(next);
            }
        }

        int queriesLength = queries.size();
        std::vector<bool> ans(queriesLength);
        for (int i = 0; i < queriesLength; ++i)
        {
            int u = queries[i][0], v = queries[i][1];
            ans[i] = isPre[u][v];
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<bool> checkIfPrerequisite(int numCourses, std::vector<std::vector<int>> &prerequisites,
                                          std::vector<std::vector<int>> &queries)
    {
        std::vector<std::vector<bool>> isPre(numCourses, std::vector<bool>(numCourses, false));
        for (const std::vector<int> &pre : prerequisites)
        {
            isPre[pre[0]][pre[1]] = true;
        }

        for (int k = 0; k < numCourses; ++k)
        {
            for (int i = 0; i < numCourses; ++i)
            {
                for (int j = 0; j < numCourses; ++j)
                {
                    if (isPre[i][k] && isPre[k][j])
                    {
                        isPre[i][j] = true;
                    }
                }
            }
        }

        int queriesLength = queries.size();
        std::vector<bool> ans(queriesLength);
        for (int i = 0; i < queriesLength; ++i)
        {
            int u = queries[i][0], v = queries[i][1];
            ans[i] = isPre[u][v];
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
