#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug/debug.h"

class Solution
{
public:
    int maxSubarraySumCircular(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
        {
            return nums[0];
        }

        // prefix[i]:nums[0:i]的和
        std::vector<int> prefix(n);
        prefix[0] = nums[0];
        for (int i = 1; i < n; ++i)
        {
            prefix[i] = prefix[i - 1] + nums[i];
        }

        // suffix[i]:nums(i:n)中包含nums[n-1]的最大连续子数组
        std::vector<int> suffix(n);
        suffix[n - 1] = 0;
        suffix[n - 2] = nums[n - 1];
        for (int i = n - 3, sum = nums[n - 1]; i >= 0; --i)
        {
            sum += nums[i + 1];
            suffix[i] = std::max(suffix[i + 1], sum);
        }

        print("prefix:");
        debug::printVector(prefix);
        print("suffix:");
        debug::printVector(suffix);


        // dp[i]:以nums[i]为结尾的子数组的最大和
        int dp[2] = {nums[0], 0};
        int ans = std::max(dp[0], prefix[0] + suffix[0]);
        std::cout << "ans = " << ans << std::endl;
        for (int i = 1; i < n; ++i)
        {
            int cur = i % 2, last = (i - 1) % 2;
            dp[cur] = std::max(dp[last] + nums[i], nums[i]);
            ans = std::max({ans, dp[cur], prefix[i] + suffix[i]});
            std::cout << "dp[" << i << "] = " << dp[cur] << ", prefix[" << i << "] + suffix[" << i << "] = "
                      << prefix[i] + suffix[i] << std::endl;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1,-2,3,-2};
    int ans = solution.maxSubarraySumCircular(nums);
    println(ans);
    return 0;
}