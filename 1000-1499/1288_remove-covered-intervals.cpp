#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int removeCoveredIntervals(std::vector<std::vector<int>>& intervals)
    {
        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) -> bool {
            if (a[0] == b[0])
                return a[1] > b[1];
            return a[0] < b[0];
        });

        int n = intervals.size(), del = 0, i = 0;
        while (i < n)
        {
            int j = i + 1;
            while (j < n && intervals[i][1] >= intervals[j][1]) // 区间j被区间i覆盖
            {
                ++j;
                ++del;
            }
            i = j;
        }
        return n - del;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}