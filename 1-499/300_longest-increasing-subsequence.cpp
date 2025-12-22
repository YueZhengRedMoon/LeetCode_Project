#include <iostream>
#include <vector>

class Solution
{
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        // dp[i]:nums[0:i]中以nums[i]结尾的最长严格递增子序列的长度
        std::vector<int> dp(nums.size(), 0);
        dp[0] = 1;
        int result = 1;

        for (int i = 1; i < nums.size(); ++i)
        {
            dp[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            if (dp[i] > result)
                result = dp[i];
        }

        return result;
    }
};

/** 贪心 + 二分查找
 *  要使上升子序列尽可能的长，需要让序列上升的尽可能慢，因此希望每次在上升子序列最后加上的那个数尽可能小
 *  时间复杂度O(nlogn) */
class Solution2
{
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        int len = 1;    // 当前子序列的长度
        int size = nums.size();
        // dp[i]:长度为i的最长上升子序列的末尾元素的最小值
        std::vector<int> dp(size + 1, 0);
        dp[1] = nums[0];

        for (int i = 1; i < size; ++i)
        {
            if (nums[i] > dp[len])
            {
                dp[++len] = nums[i];
            }
            // nums[i] <= dp[len]
            else
            {
                // 在dp数组中二分查找，找到第一个比nums[i]小的数dp[k]，并更新dp[k+1]=nums[i]
                int left = 1, right = len;
                int pos = 0;    // 如果所有数都比nums[i]大，即此时nums[i]是最小的，则要更新长度为1的最长上升子序列的末尾元素的最小值
                while (left <= right)
                {
                    int mid = (left + right) >> 1;
                    if (dp[mid] < nums[i])
                    {
                        pos = mid;  // 记录比nums[i]小的数的下标
                        left = mid + 1;
                    }
                    // dp[mid] >= nums[i]
                    else
                    {
                        right = mid - 1;
                    }
                }
                dp[pos + 1] = nums[i];
            }
        }

        return len;
    }
};

class Solution3
{
public:
    int lengthOfLIS(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> f(n);  // f[i]:以nums[i]为结尾的最长递增子序列的长度
        int ans = 1;
        for (int i = 0; i < n; ++i)
        {
            f[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    f[i] = std::max(f[i], f[j] + 1);
                }
            }
            if (f[i] > ans)
                ans = f[i];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
