#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    using Pair = std::pair<int, int>;

    int findCrossingTime(int n, int k, std::vector<std::vector<int>> &workers)
    {
        int count = 0;      // 已经搬到新仓库的箱子的数量
        int curTime = 0;    // 当前时间
        // 等待队列，大顶堆，first:过桥总时间，second:工人编号
        std::priority_queue<Pair, std::vector<Pair>, std::less<>> leftWaiting, rightWaiting;
        // 工作队列，小顶堆，first:完成工作的时间，second:工人编号
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> leftWorking, rightWorking;
        for (int i = 0; i < k; ++i)
        {
            leftWaiting.emplace(workers[i][0] + workers[i][2], i);
        }

        while (count < n)
        {
            bool timeUpdated = false;
            int id; //工人id
            // 左侧工人过桥
            while (!leftWaiting.empty() && rightWaiting.empty() && count + rightWorking.size() < n)
            {
                id = leftWaiting.top().second;  // 左侧过桥工人的id
                leftWaiting.pop();
                curTime += workers[id][0];      // 工人到达右侧的时间
                timeUpdated = true;

                // 工人到达右边后开始挑选箱子，记录其完成工作的时间
                rightWorking.emplace(curTime + workers[id][1], id);

                // 将两边工作完成的工人加入各自的等待队列
                finishWork(leftWaiting, leftWorking, workers, curTime);
                finishWork(rightWaiting, rightWorking, workers, curTime);
            }

            // 右侧工人过桥
            while (!rightWaiting.empty())
            {
                id = rightWaiting.top().second;
                rightWaiting.pop();
                curTime += workers[id][2];  // 工人到达左侧的时间
                timeUpdated = true;
                // 所有箱子都已经搬完
                if (++count == n)
                {
                    break;
                }

                // 工人到达左边后开始放箱子，记录其完成的时间
                leftWorking.emplace(curTime + workers[id][3], id);
                // 将两边工作完成的工人加入各自的等待队列
                finishWork(leftWaiting, leftWorking, workers, curTime);
                finishWork(rightWaiting, rightWorking, workers, curTime);
            }

            if (!timeUpdated)
            {
                // 已经不需要再有工人从左边到右边
                if (count + rightWorking.size() == n)
                {
                    curTime = rightWorking.top().first;
                    finishWork(rightWaiting, rightWorking, workers, curTime);
                }
                // 还需要有工人从左边到右边
                else
                {
                    if (leftWorking.empty())
                    {
                        curTime = rightWorking.top().first;
                        finishWork(rightWaiting, rightWorking, workers, curTime);
                    }
                    else if (rightWorking.empty())
                    {
                        curTime = leftWorking.top().first;
                        finishWork(leftWaiting, leftWorking, workers, curTime);
                    }
                    else
                    {
                        if (leftWorking.top().first < rightWorking.top().first)
                        {
                            curTime = leftWorking.top().first;
                            finishWork(leftWaiting, leftWorking, workers, curTime);
                        }
                        else
                        {
                            curTime = rightWorking.top().first;
                            finishWork(rightWaiting, rightWorking, workers, curTime);
                        }
                    }
                }
            }
        }

        return curTime;
    }

private:
    void finishWork(std::priority_queue<Pair, std::vector<Pair>, std::less<>> &waiting,
                    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> &working,
                    std::vector<std::vector<int>> &workers,
                    int curTime)
    {
        while (!working.empty() && working.top().first <= curTime)
        {
            int id = working.top().second;
            working.pop();
            waiting.emplace(workers[id][0] + workers[id][2], id);
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
