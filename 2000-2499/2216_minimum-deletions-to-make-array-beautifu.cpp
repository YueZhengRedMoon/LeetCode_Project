#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    int minDeletion(std::vector<int> &nums)
    {
        int n = nums.size(), i = 0, j = 0;
        while (j < n)
        {
            int cnt = 0;    // 连续相同的元素数
            do
            {
                ++j;
                ++cnt;
            }
            while (j < n && nums[j] == nums[j - 1]);
            if (cnt == 1)
            {
                ++i;
            }
            else
            {
                if (i % 2 == 0)
                    ++i;
                else
                    i += 2;
            }
        }
        return n - i + (i % 2 == 0);
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 1, 2, 2, 3, 3};
    int ans = solution.minDeletion(nums);
    logObj(ans);
    return 0;
}
