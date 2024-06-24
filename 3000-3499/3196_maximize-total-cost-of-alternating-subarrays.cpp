#include <iostream>
#include <vector>

class Solution
{
public:
    long long maximumTotalCost(std::vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];

        long long f[3] = {nums[0], std::max(nums[0] + nums[1], nums[0] - nums[1])};
        for (int i = 2; i < n; ++i)
        {
            int cur = i % 3, prev1 = (i - 1) % 3, prev2 = (i - 2) % 3;
            f[cur] = std::max(f[prev1] + nums[i], f[prev2] + nums[i - 1] - nums[i]);
        }
        return f[(n - 1) % 3];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
