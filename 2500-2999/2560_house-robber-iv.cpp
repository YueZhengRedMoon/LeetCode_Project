#include <iostream>
#include <vector>

class Solution
{
public:
    // 最小化最大值

    int minCapability(std::vector<int> &nums, int k)
    {
        int n = nums.size(), minNum = nums[0], maxNum = nums[0];
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] < minNum)
                minNum = nums[i];
            if (nums[i] > maxNum)
                maxNum = nums[i];
        }

        int left = minNum, right = maxNum;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            // 检查在nums中是否至少能选出k个不相邻的数，且其中最大的数不超过mid
            if (check(nums, k, mid))
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

private:
    // 不偷取超过存放金额超过max的房子，以及不偷取相邻的房子，是否能偷至少k个房子
    bool check(const std::vector<int> &nums, int k, int max)
    {
        int n = nums.size();
        if (n == 1)
        {
            return nums[0] <= max;
        }

        // dp[i]:偷取0~i号房子最多能偷的房间数
        int dp[2];
        dp[0] = (nums[0] <= max);
        dp[1] = (nums[0] <= max || nums[1] <= max);
        int res = std::max(dp[0], dp[1]);
        for (int i = 2; i < n && res < k; ++i)
        {
            int cur = i % 2, robLast = dp[(i - 1) % 2], notRobLast = dp[cur];
            if (nums[i] > max)
            {
                dp[cur] = std::max(robLast, notRobLast);
            }
            else
            {
                dp[cur] = std::max(robLast, notRobLast + 1);
            }
            if (dp[cur] >= res)
                res = dp[cur];
        }

        return res >= k;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
