#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

class Solution
{
public:
    int numOfMinutes(int n, int headID, std::vector<int> &manager, std::vector<int> &informTime)
    {
        std::unordered_map<int, std::vector<int>> employees;
        for (int i = 0; i < manager.size(); ++i)
        {
            if (manager[i] != -1)
            {
                employees[manager[i]].push_back(i);
            }
        }

        int time = 0;
        std::queue<std::pair<int, int>> queue;
        queue.push({headID, 0});
        while (!queue.empty())
        {
            int current = queue.front().first;
            int currentTime = queue.front().second;
            queue.pop();

            if (currentTime > time)
            {
                time = currentTime;
            }

            for (int employee : employees[current])
            {
                queue.push({employee, currentTime + informTime[current]});
            }
        }

        return time;
    }
};

/** 自底向上记忆化搜索 */
class Solution2
{
public:
    int numOfMinutes(int n, int headID, std::vector<int> &manager, std::vector<int> &informTime)
    {
        // 记忆化数组
        std::vector<int> memo(manager.size(), -1);

        std::function<int(int)> dfs = [&](int x){
            if (memo[x] >= 0)
            {
                return memo[x];
            }
            if (manager[x] < 0)
            {
                return informTime[x];
            }
            return memo[x] = dfs(manager[x]) + informTime[x];
        };

        int time = 0;
        for (int i = 0; i < manager.size(); ++i)
        {
            time = std::max(time, dfs(i));
        }

        return time;
    }
};

class Solution3
{
public:
    int numOfMinutes(int n, int headID, std::vector<int> &manager, std::vector<int> &informTime)
    {
        std::function<int(int)> dfs = [&](int x) -> int {
            if (manager[x] >= 0)
            {
                informTime[x] = dfs(manager[x]) + informTime[x];
                manager[x] = -1;
            }
             return informTime[x];
        };

        int time = 0;
        for (int i = 0; i < manager.size(); ++i)
        {
            time = std::max(time, dfs(i));
        }

        return time;
    }
};

class Solution4
{
public:
    int numOfMinutes(int n, int headID, std::vector<int> &manager, std::vector<int> &informTime)
    {
        int time = 0;
        for (int i = 0; i < n; ++i)
        {
            if (manager[i] < 0)
            {
                continue;
            }

            // 计算从i向上的累加值
            int sum = 0, x = i;
            while (manager[x] >= 0)
            {
                sum += informTime[x];
                x = manager[x];
            }
            // 此时x要么是headID，要么是一个计算过的节点
            sum += informTime[x];
            if (sum > time)
            {
                time = sum;
            }

            // 记录从i向上的每个未必计算的节点的对应的累加值
            x = i;
            while (manager[x] >= 0)
            {
                int temp = informTime[x];
                informTime[x] = sum;
                sum -= temp;
                int m = manager[x];
                manager[x] = -1;
                x = m;
            }
        }

        return time;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}