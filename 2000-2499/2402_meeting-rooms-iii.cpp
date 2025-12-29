#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

class Solution
{
public:
    using Pair = std::pair<long long, int>;

    int mostBooked(int n, std::vector<std::vector<int>>& meetings)
    {
        // 按照会议的开始时间升序排序，开始时间早的会议一定可以先占用会议室开会
        std::sort(meetings.begin(), meetings.end());

        std::priority_queue<int, std::vector<int>, std::greater<>> idle;    // 小顶堆维护可用会议室的编号
        for (int i = 0; i < n; ++i)
        {
            idle.push(i);
        }
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> inUse; // <结束时间, 会议室编号>
        std::vector<int> cnt(n, 0); // 会议室的开会次数

        for (const std::vector<int>& m : meetings)
        {
            long long start = m[0], end = m[1];

            // 在start时刻空出来的会议室
            while (!inUse.empty() && inUse.top().first <= start)
            {
                idle.push(inUse.top().second);
                inUse.pop();
            }

            int i;
            if (!idle.empty())  // 有空闲的会议室
            {
                i = idle.top();
                idle.pop();
            }
            else    // 没有空闲的会议室
            {
                // 弹出一个最早结束的会议室（若有多个同时结束，弹出编号最小的会议室）
                auto [e, room] = inUse.top();
                i = room;
                inUse.pop();
                end += e - start;   // 更新当前会议的结束时间
            }

            ++cnt[i];
            inUse.emplace(end, i);
        }

        return std::max_element(cnt.begin(), cnt.end()) - cnt.begin();
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}