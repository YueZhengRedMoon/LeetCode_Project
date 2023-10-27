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

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
