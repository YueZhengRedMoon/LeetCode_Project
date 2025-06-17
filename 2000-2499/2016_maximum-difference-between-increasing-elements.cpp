#include <iostream>
#include <vector>

class Solution
{
public:
    int maximumDifference(std::vector<int>& nums)
    {
        int ans = -1;
        int leftMin = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] > leftMin)
            {
                ans = std::max(ans, nums[i] - leftMin);
            }
            leftMin = std::min(leftMin, nums[i]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
