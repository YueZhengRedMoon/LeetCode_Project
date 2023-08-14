#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> findRightInterval(std::vector<std::vector<int>> &intervals)
    {
        int n = intervals.size();
        std::vector<std::pair<std::pair<int, int>, int>> sortedIntervals(n);
        for (int i = 0; i < n; ++i)
        {
            sortedIntervals[i].first.first = intervals[i][0];
            sortedIntervals[i].first.second = intervals[i][1];
            sortedIntervals[i].second = i;
        }
        std::sort(sortedIntervals.begin(), sortedIntervals.end(),
                  [](const std::pair<std::pair<int, int>, int> &lhs, const std::pair<std::pair<int, int>, int> &rhs) {
                      return lhs.first.first < rhs.first.first;
        });

        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i)
        {
            int end = intervals[i][1], left = 0, right = n;
            // 找到第一个起点>=end的区间
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (sortedIntervals[mid].first.first >= end)
                {
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }
            if (left < n)
            {
                ans[i] = sortedIntervals[left].second;
            }
            else
            {
                ans[i] = -1;
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<int> findRightInterval(std::vector<std::vector<int>> &intervals)
    {
        int n = intervals.size();
        std::vector<std::pair<int, int>> sortedIntervals(n);
        for (int i = 0; i < n; ++i)
        {
            sortedIntervals[i].first = intervals[i][0];
            sortedIntervals[i].second = i;
        }
        std::sort(sortedIntervals.begin(), sortedIntervals.end());

        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i)
        {
            int end = intervals[i][1], left = 0, right = n;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (sortedIntervals[mid].first >= end)
                {
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }
            if (left < n)
            {
                ans[i] = sortedIntervals[left].second;
            }
            else
            {
                ans[i] = -1;
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
