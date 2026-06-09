#include <iostream>
#include <vector>

class Solution
{
public:
    long long maxTotalValue(std::vector<int>& nums, int k)
    {
        int maxVal = nums[0], minVal = nums[0];
        for (int x : nums)
        {
            if (x > maxVal)
                maxVal = x;
            if (x < minVal)
                minVal = x;
        }
        return (long long) k * (maxVal - minVal);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}