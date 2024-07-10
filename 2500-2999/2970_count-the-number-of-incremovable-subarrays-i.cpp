#include <iostream>
#include <vector>

class Solution
{
public:
    int incremovableSubarrayCount(std::vector<int>& nums)
    {
        int n = nums.size(), i = 0;
        while (i < n - 1 && nums[i] < nums[i + 1])
            ++i;
        // nums[i]>=nums[i+1]

        if (i == n - 1)
            return (1 + n) * n / 2;

        // 前缀nums[0,i]是递增的，一共可以移除i+2个子数组：
        // 移除nums[i+1,n), nums[i, n), nums[i-1,n), ..., nums[0, n)
        int ans = i + 2;

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
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
