#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Solution
{
public:
    int intersectionSizeTwo(std::vector<std::vector<int>>& intervals)
    {
        // 按照右端点end从小到大排序
        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {return a[1] < b[1];});

        int ans = 0;
        std::set<int> run;
        for (const std::vector<int>& interval : intervals)
        {
            int start = interval[0], end = interval[1];
            auto lb = run.lower_bound(start);
            auto ub = run.upper_bound(end);
            auto it = lb;
            int d = 2;
            while (it != ub && d > 0)
            {
                ++it;
                --d;
            }
            for (int i = end; d > 0; --i)
            {
                if (run.find(i) == run.end())
                {
                    run.insert(i);
                    --d;
                    ++ans;
                }
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