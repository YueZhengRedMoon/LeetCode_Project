#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals, std::vector<int> &newInterval)
    {
        int n = intervals.size();
        // 找到第一个结束端点 >= 插入区间起始端点的区间
        int left = 0, right = n;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (intervals[mid][1] >= newInterval[0])
            {
                right = mid;
            }
            else
            {
                // intervals[mid][1] < newInterval[0]
                // intervals[mid + 1][1] 可能>= newInterval[0]
                left = mid + 1;
            }
        }

        // intervals[index][1] >= newInterval[0]
        int index = left;
        if (index == n)
        {
            intervals.push_back(newInterval);
        }
        // intervals[left][1] >= newInterval[0]
        else
        {
            // 新插入的区间不与任何区间重叠
            if (intervals[index][0] > newInterval[1])
            {
                intervals.insert(intervals.begin() + left, newInterval);
            }
            // 存在重叠的区间
            else
            {
                // 找到第一个起始端点大于新插入区间结束端点的区间
                left = index, right = n;
                while (left < right)
                {
                    int mid = (left + right) / 2;
                    if (intervals[mid][0] > newInterval[1])
                    {
                        right = mid;
                    }
                    else
                    {
                        left = mid + 1;
                    }
                }

                int index2 = left;
                intervals[index][1] = std::max(newInterval[1], intervals[index2 - 1][1]);
                intervals[index][0] = std::min(intervals[index][0], newInterval[0]);
                if (index + 1 < index2)
                {
                    intervals.erase(intervals.begin() + index + 1, intervals.begin() + index2);
                }
            }
        }
        return intervals;
    }
};

int main()
{
    Solution solution;

    std::vector<std::vector<int>> intervals2 = {{1, 5}};
    std::vector<int> newInterval2 = {0, 3};
    std::vector<std::vector<int>> ans2 = solution.insert(intervals2, newInterval2);
    debug::printVector2D(ans2);

    std::vector<std::vector<int>> intervals1 = {{1, 3}, {6, 9}};
    std::vector<int> newInterval1 = {2, 5};
    std::vector<std::vector<int>> ans1 = solution.insert(intervals1, newInterval1);
    debug::printVector2D(ans1);
    return 0;
}
