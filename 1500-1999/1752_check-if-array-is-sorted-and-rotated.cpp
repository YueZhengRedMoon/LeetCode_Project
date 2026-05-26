#include <iostream>
#include <vector>

class Solution
{
public:
    bool check(std::vector<int>& nums)
    {
        int n = nums.size();
        bool rotated = false;
        for (int i = 1; i < n; ++i)
        {
            if (nums[i - 1] > nums[i])
            {
                if (rotated)
                {
                    return false;
                }
                rotated = true;
            }
        }
        return !rotated || nums[n - 1] <= nums[0];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}