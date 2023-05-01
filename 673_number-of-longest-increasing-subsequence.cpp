#include <iostream>
#include <vector>
#include <functional>
#include "debug.h"

class Solution
{
public:
    int findNumberOfLIS(std::vector<int> &nums)
    {
        int size = nums.size();

        // dp[i]:以nums[i]结尾的最长递增子序列的长度及其数量
        std::vector<std::vector<int>> dp(size, std::vector<int>(2, 1));

        int maxLen = 1;
        int count = 1;
        for (int i = 1; i < size; ++i)
        {
            if (dp[i][0] == maxLen)
            {
                ++count;
            }
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    int len = dp[j][0] + 1;
                    if (len > dp[i][0])
                    {
                        dp[i][0] = len;
                        dp[i][1] = dp[j][1];
                        if (dp[i][0] > maxLen)
                        {
                            maxLen = dp[i][0];
                            count = dp[i][1];
                        }
                        else if (dp[i][0] == maxLen)
                        {
                            count += dp[i][1];
                        }
                    }
                    else if (len == dp[i][0])
                    {
                        dp[i][1] += dp[j][1];
                        if (dp[i][0] == maxLen)
                        {
                            count += dp[j][1];
                        }
                    }
                }
            }
        }

        debug::printVector2D(dp);

        return count;
    }
};

class Solution2
{
public:
    int findNumberOfLIS(std::vector<int> &nums)
    {
        // dp[i]:所有长度为i的递增子序列的末尾元素，dp[i]中的元素是递减的，dp[i].back()是递增的
        // count[i][j]:长度为i，末尾元素为dp[i][j]的递增子序列的数量
        std::vector<std::vector<int>> dp, count;

        for (int num : nums)
        {
            int i = binarySearch(dp.size(), [&](int mid){return dp[mid].back() >= num;});
            int c = 1;
            if (i > 0)
            {
                int k = binarySearch(dp[i - 1].size(), [&](int mid){return dp[i - 1][mid] < num;});
                c = count[i - 1].back() - count[i - 1][k];
            }
            if (i == dp.size())
            {
                dp.push_back({num});
                count.push_back({0, c});
            }
            else
            {
                dp[i].push_back(num);
                count[i].push_back(count[i].back() + c);
            }
        }

        std::cout << "dp:" << std::endl;
        debug::printVector2D(dp);
        std::cout << "count:" << std::endl;
        debug::printVector2D(count);

        return count.back().back();
    }

private:
    int binarySearch(int n, const std::function<bool(int)> &comp)
    {
        int left  = 0, right = n;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (comp(mid))
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main()
{
    Solution2 solution;
    std::vector<int> nums = {1, 2, 4, 3, 5, 4, 7, 2};
    std::vector<int> nums2 = {1,1,1,2,2,2,3,3,3};
    int count = solution.findNumberOfLIS(nums);
    std::cout << count << std::endl;
    return 0;
}
