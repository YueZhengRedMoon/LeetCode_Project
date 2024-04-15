#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minMeetingRooms(std::vector<std::vector<int>> &intervals)
    {
        int n = intervals.size();
        std::vector<std::pair<int, int>> times;
        times.reserve(2 * n);
        for (const std::vector<int> &interval : intervals)
        {
            times.emplace_back(interval[0], 1);
            times.emplace_back(interval[1], -1);
        }
        std::sort(times.begin(), times.end());

        int ans = 0, cur = 0;
        for (auto it = times.begin(); it != times.end(); ++it)
        {
            cur += it->second;
            if (cur > ans)
                ans = cur;
        }
        return ans;
    }
};

class Solution2
{
public:
    int minMeetingRooms(std::vector<std::vector<int>> &intervals)
    {
        int maxEndTime = 0;
        for (const auto& interval : intervals)
        {
            if (interval[1] > maxEndTime)
                maxEndTime = interval[1];
        }

        std::vector<int> d(maxEndTime + 2, 0);  // 差分数组
        for (const auto& interval : intervals)
        {
            int start = interval[0], end = interval[1];
            ++d[start];
            --d[end + 1];
        }

        int ans = d[0];
        for (int i = 1; i <= maxEndTime; ++i)
        {
            d[i] += d[i - 1];
            if (d[i] > ans)
                ans = d[i];
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
