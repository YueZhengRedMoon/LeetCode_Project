#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals)
    {
        std::sort(intervals.begin(), intervals.end(), less);

        std::vector<std::vector<int>> result;
        int begin = intervals[0][0], end = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i][0] > end)
            {
                result.push_back({begin, end});
                begin = intervals[i][0];
                end = intervals[i][1];
            }
            else
            {
                end = std::max(end, intervals[i][1]);
            }
        }
        result.push_back({begin, end});

        return result;
    }

private:
    static bool less(const std::vector<int> &lhs, const std::vector<int> &rhs)
    {
        return lhs[0] < rhs[0];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}