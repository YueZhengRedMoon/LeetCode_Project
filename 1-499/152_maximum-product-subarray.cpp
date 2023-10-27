#include <iostream>
#include <vector>
#include <algorithm>


class Solution
{
public:
    int maxProduct(std::vector<int> &nums)
    {
        // dp[i][0]:以nums[i]结尾的子数组的最大乘积
        // dp[i][1]:以nums[i]结尾的子数组的最小乘积
        int dp[2] = {nums[0], nums[0]};

        int ans = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            int lastMax = dp[0], lastMin = dp[1];
            dp[0] = std::max({nums[i], lastMax * nums[i], lastMin * nums[i]});
            dp[1] = std::min({nums[i], lastMax * nums[i], lastMin * nums[i]});
            if (dp[0] > ans)
            {
                ans = dp[0];
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
