#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    long long countFairPairs(std::vector<int>& nums, int lower, int upper)
    {
        std::sort(nums.begin(), nums.end());
        long long ans = 0;
        for (int j = 0; j < nums.size(); ++j)
        {
            auto r = std::upper_bound(nums.begin(), nums.begin() + j, upper - nums[j]);
            auto l = std::lower_bound(nums.begin(), nums.begin() + j, lower - nums[j]);
            ans += r - l;
        }
        return ans;
    }
};

class Solution2
{
public:
    long long countFairPairs(std::vector<int>& nums, int lower, int upper)
    {
        std::sort(nums.begin(), nums.end());
        long long ans = 0;
        int l = nums.size(), r = l;
        for (int j = 0; j < nums.size(); ++j)
        {
            while (r && nums[r - 1] > upper - nums[j])
                --r;
            while (l && nums[l - 1] >= lower - nums[j])
                --l;
            ans += std::min(r, j) - std::min(l, j);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
