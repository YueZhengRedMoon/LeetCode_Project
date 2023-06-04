#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> applyOperations(std::vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n - 1; ++i)
        {
            if (nums[i] == nums[i + 1])
            {
                nums[i] *= 2;
                nums[i + 1] = 0;
            }
        }
        std::stable_partition(nums.begin(), nums.end(), [](int num) {return num > 0;});
        return nums;
    }
};

class Solution2
{
public:
    std::vector<int> applyOperations(std::vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n - 1; ++i)
        {
            if (nums[i] == nums[i + 1])
            {
                nums[i] *= 2;
                nums[i + 1] = 0;
            }
        }
        int j = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > 0)
            {
                nums[j++] = nums[i];
            }
        }
        for (int i = j; i < n; ++i)
        {
            nums[i] = 0;
        }
        return nums;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}