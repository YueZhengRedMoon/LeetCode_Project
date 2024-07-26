#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int findValueOfPartition(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = INT_MAX;
        for (int i = 1; i < n; ++i)
        {
            ans = std::min(ans, nums[i] - nums[i - 1]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
