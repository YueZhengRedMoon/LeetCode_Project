#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    void nextPermutation(std::vector<int>& nums)
    {
        while (std::next_permutation(nums.begin(), nums.end()))
        {
            for (int num : nums)
                std::cout << num << ' ';
            std::cout << std::endl;
        }

    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {1, 2, 3, 4, 5};
    solution.nextPermutation(nums);
    return 0;
}
