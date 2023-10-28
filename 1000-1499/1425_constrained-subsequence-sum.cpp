#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include "../debug/debug.h"

class Solution
{
public:
    int constrainedSubsetSum(std::vector<int> &nums, int k)
    {
        int size = nums.size();

        // dp[i]:以nums[i]结尾的带限制子序列的最大和
        std::vector<int> dp(size);
        std::set<std::pair<int, int>, std::greater<>> window;
        window.insert({nums[0], 0});
        dp[0] = nums[0];
        int result = nums[0];
        for (int j = 1; j < size; ++j)
        {
            int i = j - k - 1;
            if (i >= 0)
            {
                window.erase({dp[i], i});
            }

            auto it = window.begin();
            dp[j] = std::max(0, it->first) + nums[j];
            window.insert({dp[j], j});

            if (dp[j] > result)
            {
                result = dp[j];
            }
        }

        debug::printVector(dp);

        return result;
    }
};

class Solution2
{
public:
    int constrainedSubsetSum(std::vector<int> &nums, int k)
    {
        int size = nums.size();
        std::vector<int> dp(size);
        std::deque<int> deque;

        int result = nums[0];
        dp[0] = nums[0];
        deque.push_back(0);

        for (int j = 1; j < size; ++j)
        {
            int i = j - k;
            while (!deque.empty() && deque.front() < i)
            {
                deque.pop_front();
            }

            dp[j] = std::max(dp[deque.front()], 0) + nums[j];
            while (!deque.empty() && dp[deque.back()] < dp[j])
            {
                deque.pop_back();
            }
            deque.push_back(j);

            if (dp[j] > result)
            {
                result = dp[j];
            }
        }

        return result;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums1 = {10,2,-10,5,20};
    std::vector<int> nums2 = {10,-2,-10,-5,20};
    int k = 2;
    int result = solution.constrainedSubsetSum(nums2, k);
    std::cout << result << std::endl;
//    result = solution.constrainedSubsetSum(nums2, k);
//    std::cout << result << std::endl;
    return 0;
}
