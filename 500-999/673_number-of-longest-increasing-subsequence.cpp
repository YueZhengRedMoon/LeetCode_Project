#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include "../debug.h"

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

        // 要计算count[i][j]，就要考虑dp[i-1]和count[i-1]
        // 因为dp[i-1]中的元素是递减的，所以可以用二分找到第一个小于num的dp[i-1][k]
        // 此时有dp[i-1][k]~dp[i-1].back()的都 < num，则num可以接在这些序列后面
        // 因此有count[i][j] = count[i-1][k] + count[i-1][k+1] + ... + count[i-1].back()，而这个可以由前缀和计算出来
        for (int num : nums)
        {
            // 找到插入位置
            // 找到第一个结尾元素大于等于num的序列dp[i]，则num可以插入到长度为i的子序列中
            int i = binarySearch(dp.size(), [&](int mid){return dp[mid].back() >= num;});
            int c = 1;
            if (i > 0)
            {
                // 计算长度为i的子序列的数量
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

/*
class Solution3
{
public:
    int findNumberOfLIS(std::vector<int> &nums)
    {
        numsSize = nums.size();
        std::vector<int> numsCopy = nums;
        std::sort(numsCopy.begin(), numsCopy.end());
        std::unordered_map<int, int> map;
        for (int i = 0, index = 1; i < numsSize; ++i)
        {
            if (map.find(numsCopy[i]) == map.end())
            {
                map[numsCopy[i]] = index++; // 存储nums中每种数第一次出现的位置
            }
        }

        tree.resize(numsSize);
        for (int i = 0; i < numsSize; ++i)
        {
            int x = map[nums[i]];

        }
    }

private:
    int numsSize;
    std::vector<std::pair<int, int>> tree;

    std::pair<int, int> query(int x)
    {
        int len = 0, cnt = 0;
        for (int i = x; i > 0; i -= lowbit(i))
        {

        }
    }

    inline int lowbit(int x)
    {
        return x & -x;
    }
};
*/

int main()
{
    Solution2 solution;
    std::vector<int> nums = {1, 2, 4, 3, 5, 4, 7, 2};
    std::vector<int> nums2 = {1,1,1,2,2,2,3,3,3};
    int count = solution.findNumberOfLIS(nums);
    std::cout << count << std::endl;
    return 0;
}
