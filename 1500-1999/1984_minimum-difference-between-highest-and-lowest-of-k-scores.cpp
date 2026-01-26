#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minimumDifference(std::vector<int>& nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int ans = INT_MAX;
        for (int i = 0, j = k - 1; j < nums.size(); ++i, ++j)
        {
            ans = std::min(ans, nums[j] - nums[i]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}