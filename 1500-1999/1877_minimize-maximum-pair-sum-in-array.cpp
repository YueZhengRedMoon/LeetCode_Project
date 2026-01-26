#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minPairSum(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        for (int i = 0, j = n - 1; i < j; ++i, --j)
        {
            ans = std::max(ans, nums[i] + nums[j]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}