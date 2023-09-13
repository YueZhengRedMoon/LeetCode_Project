#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    // 转换nums数组，如果nums[i] % m == k，则nums[i] = 1，否则nums[i] = 0
    // 则可以构建一个前缀和数组pre(长度为n+1,添加了一个前缀0，以便于计算任意的子数组的和)
    // 则子数组nums[l:r]中满足nums[i] % m == k的元素的数量cnt即为pre[R] - pre[l], R = r + 1
    // (pre[R] - pre[l]) % m == k
    // pre[R] % m - pre[l] % m == k 或 pre[R] % m - pre[l] % m + m == k
    // (pre[R] % m - k + m) % m == pre[l] % m

    long long countInterestingSubarrays(std::vector<int> &nums, int m, int k)
    {
        int n = nums.size();
        long long ans = 0, pre = 0;
        std::vector<int> cnt(n + 1, 0);
        cnt[0] = 1; // 相当于在前缀和数组中添加的前缀0，这样才能正确统计nums[0:r]这样的子数组
        for (int num : nums)
        {
            // 累计前缀和，当计算到pre[R]时，需要统计有多少个pre[l]使得(pre[R] - pre[l]) % m == k
            if (num % m == k)
                pre = (pre + 1) % m;
            // 根据上面的公式变形有：pre[l] % m == (pre[R] % m - k + m) % m
            long long pre2 = (pre - k + m) % m;
            // 统计满足条件的子数组的个数
            if (pre2 <= n)
                ans += cnt[pre2];
            // 在累计前缀和的同时，使用哈希表记录前缀和%m的出现次数
            ++cnt[pre];
            // 注意:必须先统计满足子数组的个数，再更新哈希表，否则就会出现允许l == R(即l - 1 == r)的情况，这不是一个子数组
        }
        return ans;
    }
};

// 超时
class Solution2
{
public:
    long long countInterestingSubarrays(std::vector<int> &nums, int modulo, int k)
    {
        int n = nums.size();
        std::vector<int> indices;   // 满足nums[i] % modulo == k的索引
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] % modulo == k)
                indices.push_back(i);
        }

        long long ans = 0;
        int m = indices.size();
        for (int right = k; right <= m; right += modulo)
        {
            if (right == 0)
                continue;
            for (int l = 0, r = right - 1; r < m; ++l, ++r)
            {
                long long leftSide = l > 0 ? (indices[l] - indices[l - 1]) : indices[l] + 1;
                long long rightSide = r + 1 < m ? (indices[r + 1] - indices[r]) : n - indices[r];
                ans += leftSide * rightSide;
            }
        }

        if (k == 0)
        {
            if (m == 0)
            {
                ans += subArrayCount(n);
            }
            else
            {
                if (indices[0] > 0)
                {
                    ans += subArrayCount(indices[0]);
                }
                for (int i = 0; i < m - 1; ++i)
                {
                    ans += subArrayCount(indices[i + 1] - indices[i] - 1);
                }
                if (indices[m - 1] < n - 1)
                {
                    ans += subArrayCount(n - indices[m - 1] - 1);
                }
            }
        }

        return ans;
    }

private:
    long long subArrayCount(long long n)
    {
        return n * (n + 1) / 2;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {3, 1, 9, 6};
    int modulo = 3, k = 0;
    int ans = solution.countInterestingSubarrays(nums, modulo, k);
    logObj(ans);
    return 0;
}
