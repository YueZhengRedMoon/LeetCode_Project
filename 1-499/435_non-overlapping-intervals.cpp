#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>> &intervals)
    {
        std::sort(intervals.begin(), intervals.end(), less);

        std::cout << "排序后结果：";
        for (const auto &interval : intervals)
        {
            std::cout << "[" << interval[0] << ", " << interval[1] << "] ";
        }
        std::cout << std::endl;

        int remove = 0;
        int begin = intervals.back()[0];
        for (int i = intervals.size() - 2; i >= 0; --i)
        {
            if (intervals[i][1] > begin)
            {
                ++remove;
                std::cout << "移除[" << intervals[i][0] << ", " << intervals[i][1] << ']' << std::endl;
            }
            else
            {
                begin = intervals[i][0];
            }
        }
        return remove;
    }

private:
    static bool less(const std::vector<int> &lhs, const std::vector<int> &rhs)
    {
//        if (lhs[0] == rhs[0])
//        {
//            return lhs[1] > rhs[1];
//        }
        return lhs[0] < rhs[0];
    }
};

int main()
{
    std::vector<std::vector<int>> intervals = {{1,2},{2,3},{3,4},{1,3}};
    Solution solution;
    std::cout << solution.eraseOverlapIntervals(intervals) << std::endl;
    return 0;
}