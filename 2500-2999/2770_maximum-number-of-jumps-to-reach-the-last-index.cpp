#include <iostream>
#include <vector>

class Solution
{
public:
    int maximumJumps(std::vector<int>& nums, int target)
    {
        int n = nums.size();
        std::vector<int> f(n, -1);
        f[0] = 0;
        for (int j = 1; j < n; ++j)
        {
            for (int i = 0; i < j; ++i)
            {
                if (f[i] != -1 && std::abs(nums[i] - nums[j]) <= target)
                {
                    f[j] = std::max(f[j], f[i] + 1);
                }
            }
        }
        return f[n - 1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}