#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Solution
{
public:
    int maxEvents(std::vector<std::vector<int>>& events)
    {
        int maxDay = 0;
        std::unordered_map<int, std::vector<int>> eEndDayMap;    // eEndDayMap[i]:于第i天开始的所有会议的结束日期
        for (int i = 0; i < events.size(); ++i)
        {
            int startDay = events[i][0], endDay = events[i][1];
            eEndDayMap[startDay].push_back(endDay);
            if (endDay > maxDay)
                maxDay = endDay;
        }

        int ans = 0;
        std::priority_queue<int, std::vector<int>, std::greater<>> minEndDayHeap;
        for (int d = 1; d <= maxDay; ++d)
        {
            if (eEndDayMap.find(d) != eEndDayMap.end())
            {
                for (int endDay : eEndDayMap[d])
                {
                    minEndDayHeap.push(endDay);
                }
            }

            while (!minEndDayHeap.empty() && minEndDayHeap.top() < d)
            {
                minEndDayHeap.pop();
            }

            if (!minEndDayHeap.empty()) // 此时，minEndDayHeap.top() >= d
            {
                ++ans;
                minEndDayHeap.pop();
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
