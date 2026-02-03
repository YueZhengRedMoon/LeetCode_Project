#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumCost(std::vector<int>& nums)
    {
        int n = nums.size(), min1 = INT_MAX, min2 = INT_MAX;
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] <= min1)
            {
                min2 = min1;
                min1 = nums[i];
            }
            else if (nums[i] < min2)    // nums[i] > min1
            {
                min2 = nums[i];
            }
        }
        return nums[0] + min1 + min2;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}