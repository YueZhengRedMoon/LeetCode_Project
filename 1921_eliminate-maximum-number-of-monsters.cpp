#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int eliminateMaximum(std::vector<int> &dist, std::vector<int> &speed)
    {
        int n = dist.size(), ans = 1;
        // 计算所有怪物到达城市所需要的时间
        std::vector<int> &time = dist;
        for (int i = 0; i < n; ++i)
        {
            if (dist[i] == 0)
                return 0;
            time[i] = (dist[i] / speed[i]) + ((dist[i] % speed[i]) > 0);
        }
        // 根据怪物到达的时间排序
        std::sort(time.begin(), time.end());

        for (int i = 0, j = 0; i < n; ++i, ++j)
        {
            if (time[i] <= j)
                break;
            ++ans;
        }

        return ans;
    }
};

class Solution2
{
public:
    int eliminateMaximum(std::vector<int> &dist, std::vector<int> &speed)
    {
        int n = dist.size();
        std::vector<int> count(n, 0);   // 对每只怪物的最迟消灭时间进行计数
        for (int i = 0; i < n; ++i)
        {
            int time = (dist[i] - 1) / speed[i];    // 怪物需要在time时间内被消灭
            // 因为怪物一共有n只，最迟n时刻就能消灭掉所有怪物，所以对于时间超过n的怪物可以直接忽略
            if (time < n)
                ++count[time];
        }

        int shootCnt = 0;   // 可以射击的次数，没分钟累积一点
        for (int i = 0; i < n; ++i)
        {
            ++shootCnt;
            shootCnt -= count[i];
            if (shootCnt < 0)
                return i + 1;
        }

        return n;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
