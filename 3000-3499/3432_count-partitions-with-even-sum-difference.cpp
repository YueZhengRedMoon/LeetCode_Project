#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int countPartitions(std::vector<int>& nums)
    {
        int ans = 0, leftSum = 0, rightSum = std::accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        for (int i = 0; i < n - 1; ++i)
        {
            leftSum += nums[i];
            rightSum -= nums[i];
            if (std::abs(leftSum - rightSum) % 2 == 0)
                ++ans;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}