#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> findIndices(std::vector<int> &nums, int indexDifference, int valueDifference)
    {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + indexDifference; j < n; ++j)
            {
                if (std::abs(nums[i] - nums[j]) >= valueDifference)
                {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
