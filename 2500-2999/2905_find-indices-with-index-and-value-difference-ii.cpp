#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> findIndices(std::vector<int> &nums, int indexDifference, int valueDifference)
    {
        int n = nums.size(), maxIndex = 0, minIndex = 0;
        for (int j = indexDifference; j < n; ++j)
        {
            int i = j - indexDifference;
            if (nums[i] > nums[maxIndex])
                maxIndex = i;
            else if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[maxIndex] - nums[j] >= valueDifference)
                return {maxIndex, j};
            if (nums[j] - nums[minIndex] >= valueDifference)
                return {minIndex, j};
        }
        return {-1, -1};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
