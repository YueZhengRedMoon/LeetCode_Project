#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    bool canAttendMeetings(std::vector<std::vector<int>> &intervals)
    {
        bool hasOverlapIntervals = false;
        std::sort(intervals.begin(), intervals.end(),
                  [&](const std::vector<int> &lhs, const std::vector<int> &rhs)
                  {
                        if (lhs[0] == rhs[0])
                        {
                            hasOverlapIntervals = true;
                            return lhs[1] < rhs[1];
                        }
                        return lhs[0] < rhs[0];
                  });
        if (hasOverlapIntervals)
            return false;

        int n = intervals.size();
        for (int i = 0; i < n - 1; ++i)
        {
            if (intervals[i][1] > intervals[i + 1][0])
                return false;
        }

        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}