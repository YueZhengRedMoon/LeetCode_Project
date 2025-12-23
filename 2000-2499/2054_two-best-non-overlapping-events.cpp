#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxTwoEvents(std::vector<std::vector<int>>& events)
    {
        // 按照会议的结束时间升序排序
        std::sort(events.begin(), events.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] < b[1];
        });

        // <endTime, value>单调栈，从栈底到栈顶，结束时间递增，价值递增
        std::vector<std::pair<int, int>> stack({{0, 0}});   // 在栈底添加一个哨兵

        int ans = 0;
        for (const std::vector<int>& e : events)
        {
            int startTime = e[0], value = e[2];
            // 二分查找最后一个结束时间 < startTime 的活动
            int left = 0, right = stack.size(), i = 0;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (stack[mid].first < startTime)
                {
                    i = mid;
                    left = mid + 1;
                }
                else    // stack[mid].first >= startTime
                {
                    right = mid;
                }
            }
            ans = std::max(ans, stack[i].second + value);
            if (value > stack.back().second)
            {
                stack.emplace_back(e[1], value);
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