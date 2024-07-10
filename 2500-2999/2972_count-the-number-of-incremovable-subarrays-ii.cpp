#include <iostream>
#include <vector>

class Solution
{
public:
    long long incremovableSubarrayCount(std::vector<int>& nums)
    {
        int n = nums.size(), i = 0;
        while (i < n - 1 && nums[i] < nums[i + 1])
            ++i;
        // nums[i]>=nums[i+1]

        if (i == n - 1)
            return (1ll + n) * n / 2ll;

        // 前缀nums[0,i]是递增的，一共可以移除i+2个子数组：
        // 移除nums[i+1,n), nums[i, n), nums[i-1,n), ..., nums[0, n)
        long long ans = i + 2;

        // 枚举保留的后缀nums[j, n)
        for (int j = n - 1; j == n - 1 || nums[j] < nums[j + 1]; --j)
        {
            while (i >= 0 && nums[i] >= nums[j])
                --i;
            // nums[i] < nums[j]
            // 可以保留前缀nums[0,i], nums[0,i-1], ..., nums[0, 0], nums[0, -1](不保留前缀)共i+2个
            ans += i + 2;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {2, 4, 6, 3, 1, 3, 1, 3, 1, 7, 8};
    long long ans = solution.incremovableSubarrayCount(nums);
    std::cout << ans << std::endl;
    return 0;
}
