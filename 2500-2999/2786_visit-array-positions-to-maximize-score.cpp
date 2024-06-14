#include <iostream>
#include <vector>

class Solution
{
public:
    long long maxScore(std::vector<int>& nums, int x)
    {
        long long maxOddScore, maxEvenScore;    // 最大奇数得分、最大偶数得分
        long long ans = nums[0];
        if (nums[0] % 2)    // nums[0]是奇数
        {
            maxOddScore = nums[0];
            maxEvenScore = INT_MIN;
        }
        else    // nums[0]是偶数
        {
            maxOddScore = INT_MIN;
            maxEvenScore = nums[0];
        }

        int n = nums.size();
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] % 2)    // nums[i]是奇数
            {
                maxOddScore = std::max(maxOddScore + nums[i], maxEvenScore + nums[i] - x);
            }
            else    // nums[i]是偶数
            {
                maxEvenScore = std::max(maxEvenScore + nums[i], maxOddScore + nums[i] - x);
            }
            ans = std::max(ans, std::max(maxOddScore, maxEvenScore));
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
