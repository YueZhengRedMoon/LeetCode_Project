#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> findMissingRanges(std::vector<int> &nums, int lower, int upper)
    {
        int n = nums.size();
        if (n == 0)
        {
            return {{lower, upper}};
        }

        std::vector<std::vector<int>> ans;
        if (nums[0] - lower >= 1)
        {
            ans.push_back({lower, nums[0] - 1});
        }
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] - nums[i - 1] > 1)
            {
                ans.push_back({nums[i - 1] + 1, nums[i] - 1});
            }
        }
        if (upper - nums[n - 1] >= 1)
        {
            ans.push_back({nums[n - 1] + 1, upper});
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}