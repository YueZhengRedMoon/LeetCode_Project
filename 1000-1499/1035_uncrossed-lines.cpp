#include <iostream>
#include <vector>

class Solution
{
public:
    int maxUncrossedLines(std::vector<int> &nums1, std::vector<int> &nums2)
    {
        // dp[i][j]:nums1[0:i]与nums[0:j]最多可以连多少根线
        std::vector<std::vector<int>> dp(nums1.size() + 1, std::vector<int>(nums2.size() + 1, 0));

        for (int i = 1; i <= nums1.size(); ++i)
        {
            for (int j = 1; j <= nums2.size(); ++j)
            {
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }

        return dp[nums1.size()][nums2.size()];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}