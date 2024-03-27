#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug/debug.h"

class Solution
{
public:
    int countWays(std::vector<std::vector<int>>& ranges)
    {
        int n = ranges.size();
        std::sort(ranges.begin(), ranges.end(),
                  [&](const std::vector<int>& a, const std::vector<int>& b) {return a[0] < b[0];});
        int ans = 1, maxEnd = -1;
        for (const std::vector<int>& range : ranges)
        {
            if (range[0] > maxEnd)
            {
                ans = ans * 2 % 1'000'000'007;
            }
            maxEnd = std::max(range[1], maxEnd);
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> ranges1 = {{1, 3}, {10, 20}, {2, 5}, {4, 8}};
    std::vector<std::vector<int>> ranges2 = {{1, 3}, {2, 5}};
    std::vector<std::vector<int>> ranges3 = {{5,11},{20,22},{1,3},{21,22},{11,11}};
    int ans = solution.countWays(ranges3);
    std::cout << ans << std::endl;
    return 0;
}
