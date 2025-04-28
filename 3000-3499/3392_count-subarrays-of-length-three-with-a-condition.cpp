#include <iostream>
#include <vector>

class Solution
{
public:
    int countSubarrays(std::vector<int>& nums)
    {
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n - 2; ++i)
        {
            ans += (nums[i] + nums[i + 2]) * 2 == nums[i + 1];
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
