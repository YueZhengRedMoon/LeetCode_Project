#include <iostream>
#include <vector>

class Solution
{
public:
    int alternatingSubarray(std::vector<int> &nums)
    {
        int n = nums.size(), ans = -1, i = 1;
        while (i < n)
        {
            if (nums[i] - nums[i - 1] == 1)
            {
                int delta = -1, j = i + 1;
                while (j < n && nums[j] - nums[j - 1] == delta)
                {
                    ++j;
                    delta = 0 - delta;
                }
                ans = std::max(ans, j - i + 1);
                i = j;
            }
            else
            {
                ++i;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
