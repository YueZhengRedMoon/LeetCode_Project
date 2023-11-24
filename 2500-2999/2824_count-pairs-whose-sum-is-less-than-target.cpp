#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    int countPairs(std::vector<int> &nums, int target)
    {
        std::sort(nums.begin(), nums.end());
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; ++i)
        {
            int j = target - nums[i];
            // 在nums[i+1, n)中找到<j的最后一个数
            auto begin = nums.begin() + i + 1;
            auto it = std::lower_bound(begin, nums.end(), j);   // *it >= j
            if (it != begin)
            {
                --it;   // it此时指向<j的最大的数
                ans += (it - begin) + 1;
            }
            else
            {
                break;
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {-6,2,5,-2,-7,-1,3};
    int target = -2;
    int ans = solution.countPairs(nums, target);
    logObj(ans);
    return 0;
}
