#include <iostream>
#include <vector>

class Solution
{
public:
    int longestSubarray(std::vector<int> &nums)
    {
        int numsSize = nums.size();
        // 以nums[i]结尾的最长连续全1子数组的长度
        std::vector<int> pre(numsSize);
        pre[0] = nums[0];
        for (int i = 1; i < numsSize; ++i)
        {
            if (nums[i] == 0)
                pre[i] = 0;
            else
                pre[i] = pre[i - 1] + 1;
        }

        // 以nums[i]开头的最长连续全1子数组的长度
        std::vector<int> suf(numsSize);
        suf[numsSize - 1] = nums[numsSize - 1];
        for (int i = numsSize - 2; i >= 0; --i)
        {
            if (nums[i] == 0)
                suf[i] = 0;
            else
                suf[i] = suf[i + 1] + 1;
        }

        int result = 0;
        for (int i = 0; i < numsSize; ++i)
        {
            int preSum = (i == 0 ? 0 : pre[i - 1]);
            int sufSum = (i == numsSize - 1 ? 0 : suf[i + 1]);
            result = std::max(result, preSum + sufSum);
        }

        return result;
    }
};

class Solution2
{
public:
    int longestSubarray(std::vector<int> &nums)
    {
        // dp0[i]:以nums[i]结尾的最长连续全1子数组的长度
        // dp1[i]:以nums[i]结尾的可以删除一个0后的最长连续全1子数组的长度
        int dp0 = 0, dp1 = 0;

        int result = 0;
        for (int num : nums)
        {
            if (num == 0)
            {
                dp1 = dp0;  // 删除num
                dp0 = 0;    // 重新记录连续全1子数组的长度
            }
            else
            {
                ++dp0;
                ++dp1;
            }
            if (dp1 > result)
            {
                result = dp1;
            }
        }
        if (result == nums.size())
        {
            --result;
        }
        return result;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
