#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxSum(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end(), std::greater<>());
        auto last = std::unique(nums.begin(), nums.end());

        // 所有元素都是重复的 或 所有元素都 <= 0
        if (last == nums.begin() || nums[0] <= 0)
        {
            return nums[0];
        }

        int ans = 0;
        for (auto it = nums.begin(); it != last && *it > 0; ++it)
            ans += *it;

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
