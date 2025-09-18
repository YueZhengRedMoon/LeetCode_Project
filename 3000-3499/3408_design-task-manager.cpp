#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <tuple>

class TaskManager
{
public:
    TaskManager(std::vector<std::vector<int>>& tasks)
    {
        for (const auto& task : tasks)
        {
            int userId = task[0], taskId = task[1], priority = task[2];
            map[taskId] = {priority, userId};
            maxHeap.emplace(priority, taskId, userId);
        }
    }

    void add(int userId, int taskId, int priority)
    {
        map[taskId] = {priority, userId};
        maxHeap.emplace(priority, taskId, userId);
    }

    void edit(int taskId, int newPriority)
    {
        add(map[taskId].second, taskId, newPriority);
    }

    void rmv(int taskId)
    {
        map[taskId].first = -1; // 将优先级修改为-1以表示删除
    }

    int execTop()
    {
        while (!maxHeap.empty())
        {
            auto [priority, taskId, userId] = maxHeap.top();
            maxHeap.pop();
            if (map[taskId].first == priority && map[taskId].second == userId)
            {
                rmv(taskId);
                return userId;
            }
        }
        return -1;
    }

private:
    std::unordered_map<int, std::pair<int, int>> map;           // 每个任务对应的最新优先级和所属用户
    std::priority_queue<std::tuple<int, int, int>> maxHeap;     // <priority, taskId, userId>大顶堆
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
