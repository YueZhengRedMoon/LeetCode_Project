#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int pivotIndex(std::vector<int> &nums)
    {
        int size = nums.size();
        if (size == 1)
        {
            return 0;
        }

        int leftSum = 0;
        int rightSum = std::accumulate(nums.rbegin(), nums.rend() - 1, 0);
        for (int i = 0; i < size; ++i)
        {
            if (leftSum == rightSum)
            {
                return i;
            }
            leftSum += nums[i];
            rightSum = (i < size - 1 ? rightSum - nums[i + 1] : 0);
        }

        return -1;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}