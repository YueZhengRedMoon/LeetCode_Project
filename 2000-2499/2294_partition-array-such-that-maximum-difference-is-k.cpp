#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int partitionArray(std::vector<int>& nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int ans = 1, minVal = nums[0];
        for (int x : nums)
        {
            if (x - minVal > k)
            {
                ++ans;
                minVal = x;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
