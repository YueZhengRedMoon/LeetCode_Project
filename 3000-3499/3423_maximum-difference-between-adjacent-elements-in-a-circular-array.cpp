#include <iostream>
#include <vector>

class Solution
{
public:
    int maxAdjacentDistance(std::vector<int>& nums)
    {
        int n = nums.size();
        int ans = std::abs(nums[0] - nums[n - 1]);
        for (int i = 1; i < n; ++i)
        {
            ans = std::max(ans, std::abs(nums[i] - nums[i - 1]));
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
