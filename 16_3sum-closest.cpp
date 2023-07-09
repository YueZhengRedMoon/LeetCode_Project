#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    int threeSumClosest(std::vector<int> &nums, int target)
    {
        std::sort(nums.begin(), nums.end());
        int minAbsDelta = 0x3f3f3f3f, n = nums.size(), delta = 0x3f3f3f3f;
        for (int i = 0; i < n - 2; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int left = i + 1, right = n - 1;
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];
                int temp = std::abs(sum - target);
                if (temp == 0)
                    return target;
                if (temp < minAbsDelta)
                {
                    minAbsDelta = temp;
                    delta = sum - target;
                }
                if (sum > target)
                {
                    do
                    {
                        --right;
                    } while (left < right && nums[right] == nums[right + 1]);
                }
                // sum < target
                else
                {
                    do
                    {
                        ++left;
                    } while (left < right && nums[left] == nums[left - 1]);
                }
            }
        }

        return target + delta;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {-1,2,1,-4};
    int target = 1;
    int ans = solution.threeSumClosest(nums, target);
    println(ans);
    return 0;
}