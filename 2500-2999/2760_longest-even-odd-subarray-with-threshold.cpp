#include <iostream>
#include <vector>

class Solution
{
public:
    int longestAlternatingSubarray(std::vector<int> &nums, int threshold)
    {
        int ans = 0, n = nums.size();
        for (int l = 0, r; l < n; ++l)
        {
            if (nums[l] % 2 != 0 || nums[l] > threshold)
                continue;

            for (r = l + 1; r < n; ++r)
            {
                if (nums[r] > threshold || (nums[r] % 2 == nums[r - 1] % 2))
                    break;
            }

            ans = std::max(ans, r - l);
        }
        return ans;
    }
};

class Solution2
{
public:
    int longestAlternatingSubarray(std::vector<int> &nums, int threshold)
    {
        int n = nums.size(), ans = 0, i = 0;
        while (i < n)
        {
            if (nums[i] > threshold || nums[i] % 2)
            {
                ++i;
                continue;
            }
            int start = i++;    // 记录这一组开始的位置，从下一个位置开始判断
            while (i < n && nums[i] <= threshold && nums[i] % 2 != nums[i - 1] % 2)
                ++i;
            // 从start到i-1是满足题目要求的子数组
            ans = std::max(ans, i - start);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
