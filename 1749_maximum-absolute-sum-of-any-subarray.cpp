#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxAbsoluteSum(std::vector<int> &nums)
    {
        int dpMax = nums[0], dpMin = nums[0], ans = std::abs(nums[0]), n = nums.size();
        for (int i = 1; i < n; ++i)
        {
            dpMax = std::max(dpMax + nums[i], nums[i]);
            dpMin = std::min(dpMin + nums[i], nums[i]);
            ans = std::max({ans, std::abs(dpMax), std::abs(dpMin)});
        }
        return ans;
    }
};

class Solution2
{
public:
    int maxAbsoluteSum(std::vector<int> &nums)
    {
        int n = nums.size(), min = std::min(nums[0], 0), max = std::max(nums[0], 0);
        for (int i = 1; i < n; ++i)
        {
            nums[i] += nums[i - 1];
            if (nums[i] > max)
                max = nums[i];
            else if (nums[i] < min)
                min = nums[i];
        }
        return max - min;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}