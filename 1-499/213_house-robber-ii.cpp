#include <iostream>
#include <vector>

class Solution
{
public:
    int rob(std::vector<int> &nums)
    {
        if (nums.size() == 1)
            return nums[0];

        // 如果偷了第0家，就不能偷第n-1家

        // dpRobFirst[i]:偷第0家时，偷到第i家可以偷到的最大金额
        std::vector<int> dpRobFirst(nums.size(), 0);
        dpRobFirst[0] = nums[0];
        dpRobFirst[1] = nums[0];
        for (int i = 2; i < nums.size() - 1; ++i)
        {
            dpRobFirst[i] = std::max(dpRobFirst[i - 2] + nums[i], dpRobFirst[i - 1]);
        }
        dpRobFirst[nums.size() - 1] = dpRobFirst[nums.size() - 2];

        // dpNotRobFirst[i]:不偷第1家时，偷到第i家可以偷到的最大金额
        std::vector<int> dpNotRobFirst(nums.size(), 0);
        dpNotRobFirst[1] = nums[1];
        for (int i = 2; i < nums.size(); ++i)
        {
            dpNotRobFirst[i] = std::max(dpNotRobFirst[i - 2] + nums[i], dpNotRobFirst[i - 1]);
        }

        return std::max(dpRobFirst[nums.size() - 1], dpNotRobFirst[nums.size() - 1]);
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}