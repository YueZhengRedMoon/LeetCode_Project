#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfArithmeticSlices(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3) return 0;

        int ans = 0;
        int curDelta = nums[1] - nums[0];
        int begin = 0;  // 等差数量的起始区间
        for (int i = 2; i < n; ++i)
        {
            int delta = nums[i] - nums[i - 1];
            // nums[begin:i-1]可以构成等差数量
            if (delta != curDelta)
            {
                int len = i - begin;    // 等差数列的长度
                if (len >= 3)
                {
                    for (int j = 3; j <= len; ++j)
                    {
                        ans += len - j + 1;
                    }
                }
                begin = i - 1;
                curDelta = delta;
            }
        }
        // nums[begin:n-1]是等差数列
        int len = n - begin;
        if (len >= 3)
        {
            for (int j = 3; j <= len; ++j)
            {
                ans += len - j + 1;
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    int numberOfArithmeticSlices(std::vector<int> &nums)
    {
        int n = nums.size();
        if (n < 3) return 0;
        int curDelta = nums[0] - nums[1], t = 0, ans = 0;
        for (int i = 2; i < n; ++i)
        {
            int delta = nums[i - 1] - nums[i];
            if (delta == curDelta)
            {
                ++t;
            }
            else
            {
                curDelta = delta;
                t = 0;
            }
            ans += t;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 2, 3, 4, 0, 2, 4, 6, 8, 1, 0, 11, 13, 15, 17};
    int ans = solution.numberOfArithmeticSlices(nums);
    std::cout << ans << std::endl;
    return 0;
}
