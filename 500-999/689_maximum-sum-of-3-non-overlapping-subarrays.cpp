#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include "debug.h"

class Solution
{
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k)
    {
        std::vector<int> ans(3);
        int n = nums.size();
        int sum1 = 0, maxSum1 = 0, maxSum1Idx = 0;
        int sum2 = 0, maxSum12 = 0, maxSum12Idx1 = 0, maxSum12Idx2 = 0;
        int sum3 = 0, maxTotal = 0;

        for (int i = k * 2; i < n; ++i)
        {
            sum1 += nums[i - k * 2];
            sum2 += nums[i - k];
            sum3 += nums[i];

            if (i >= 3 * k - 1)
            {
                if (sum1 > maxSum1)
                {
                    maxSum1 = sum1;
                    maxSum1Idx = i - 3 * k + 1;
                }
                if (maxSum1 + sum2 > maxSum12)
                {
                    maxSum12 = maxSum1 + sum2;
                    maxSum12Idx1 = maxSum1Idx;
                    maxSum12Idx2 = i - 2 * k + 1;
                }
                if (maxSum12 + sum3 > maxTotal)
                {
                    ans[0] = maxSum12Idx1;
                    ans[1] = maxSum12Idx2;
                    ans[2] = i - k + 1;
                    maxTotal = maxSum12 + sum3;
                }

                sum1 -= nums[i - 3 * k + 1];
                sum2 -= nums[i - 2 * k + 1];
                sum3 -= nums[i - k + 1];
            }
        }

        return ans;
    }
};

// 超时
class Solution2
{
public:
    struct Status
    {
        int sum;
        int index1;
        int index2;
        int index3;
    };

    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        // 计算前缀和
        std::vector<int> prefix(n + 1, 0);  // prefix[i]:nums[0,i)的和, prefix[i] = 0
        for (int i = 0; i < n; ++i)
        {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        // 根据前缀和计算任意区间[begin, end)的和
        std::function<int(int, int)> rangeSum = [&prefix](int begin, int end) -> int {
            return prefix[end] - prefix[begin];
        };

        // 从nums[i, n)中选择j个长度为k，互不重叠的子数组，这些子数组的全部项的最大和
        std::unordered_map<int, Status> memo;
        std::function<int(int, int)> hash = [](int i, int j) -> int { return j * 100000 + i; };
        std::function<Status(int, int)> dfs = [&](int i, int j) -> Status {
            int key = hash(i, j);
            auto it = memo.find(key);
            if (it != memo.end())
                return it->second;

            if (j == 3)
            {
                int maxSum = 0, index1 = -1, index2 = -1, index3 = -1;
                for (; i <= n - j * k; ++i)
                {
                    int sum1 = rangeSum(i, i + k);
                    Status status2 = dfs(i + k, 2);
                    if (sum1 + status2.sum > maxSum)
                    {
                        maxSum = sum1 + status2.sum;
                        index1 = i;
                        index2 = status2.index2;
                        index3 = status2.index3;
                    }
                }
                return memo[key] = {maxSum, index1, index2, index3};
            }
            else if (j == 2)
            {
                int maxSum = 0, index2 = -1, index3 = -1;
                for (; i <= n - j * k; ++i)
                {
                    int sum2 = rangeSum(i, i + k);
                    Status status3 = dfs(i + k, 1);
                    if (sum2 + status3.sum > maxSum)
                    {
                        maxSum = sum2 + status3.sum;
                        index2 = i;
                        index3 = status3.index3;
                    }
                }
                return memo[key] = {maxSum, -1, index2, index3};
            }
            else    // j == 1
            {
                int maxSum = 0, index3 = -1;
                for (; i <= n - k; ++i)
                {
                    int sum = rangeSum(i, i + k);
                    if (sum > maxSum)
                    {
                        maxSum = sum;
                        index3 = i;
                    }
                }
                return memo[key] = {maxSum, -1, -1, index3};
            }
        };

        Status ans = dfs(0, 3);
        return {ans.index1, ans.index2, ans.index3};
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {7,13,20,19,19,2,10,1,1,19};
    int k = 3;
    std::vector<int> ans = solution.maxSumOfThreeSubarrays(nums, k);
    debug::printVector(ans);
    return 0;
}
