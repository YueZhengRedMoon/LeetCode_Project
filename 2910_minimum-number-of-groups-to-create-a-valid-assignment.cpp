#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include "debug.h"

class Solution
{
public:
    int minGroupsForValidAssignment(std::vector<int> &nums)
    {
        int n = nums.size();
        std::unordered_map<int, int> counter;
        for (int num : nums)
            ++counter[num];

        int minCnt = n;
        for (auto [_, cnt] : counter)
            if (cnt < minCnt)
                minCnt = cnt;

        for (int k = minCnt; k > 0; --k)
        {
            int ans = 0;
            for (auto &[_, c] : counter)
            {
                if (c / k < c % k)
                {
                    ans = 0;
                    break;
                }
                ans += (c + k) / (k + 1);
            }
            if (ans)
                return ans;
        }

        return -1;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1,1,1,1,2,2,2,1,2,1,1};
    int ans = solution.minGroupsForValidAssignment(nums);
    logObj(ans);
    return 0;
}