#include <iostream>
#include <vector>

class Solution
{
public:
    int firstMissingPositive(std::vector<int> &nums)
    {
        int n = nums.size();
        for (int &num : nums)
        {
            if (num <= 0)
            {
                num = n + 1;
            }
        }

        for (int num : nums)
        {
            int numAbs = std::abs(num);
            if (numAbs <= n)
            {
                nums[numAbs - 1] = -std::abs(nums[numAbs - 1]);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > 0)
            {
                return i + 1;
            }
        }
        return n + 1;
    }
};

int main()
{

    return 0;
}