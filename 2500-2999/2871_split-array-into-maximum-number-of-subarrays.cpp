#include <iostream>
#include <vector>
#include <limits>
#include "../debug/debug.h"

class Solution
{
public:
    int maxSubarrays(std::vector<int> &nums)
    {
        const int inf = std::numeric_limits<int>::max();
        int n = nums.size();
        std::vector<int> rightAndSum(n);
        rightAndSum[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i)
        {
            rightAndSum[i] = nums[i] & rightAndSum[i + 1];
        }
        int ans = 1, andSum = inf;
        for (int i = 0; i < n - 1; ++i)
        {
            andSum &= nums[i];
            if (andSum == rightAndSum[i + 1] && andSum == 0)
            {
                ++ans;
                andSum = inf;
            }
        }

        return ans + 1;
    }
};

class Solution2
{
public:
    int maxSubarrays(std::vector<int> &nums)
    {
        int ans = 0;
        int a = -1; // -1就是111...1，和任何数AND都等于那个数
        for (int x : nums)
        {
            a &= x;
            if (a == 0)
            {
                ++ans;
                a = -1;
            }
        }
        return std::max(ans, 1);
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1,0,2,0,1,2};
    int ans = solution.maxSubarrays(nums);
    logObj(ans);
    return 0;
}
