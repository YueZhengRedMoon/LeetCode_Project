#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution
{
public:
    bool canPartitionKSubsets(std::vector<int> &nums, int k)
    {
        int sum = 0;
        int maxNum = 0;
        for (int num : nums)
        {
            sum += num;
            if (num > maxNum)
            {
                maxNum = num;
            }
        }

        int size = sum / k; // 每个非空子集的和
        if (sum % k != 0 || maxNum > size)
        {
            return false;
        }

        int n = nums.size();
        // dp[s]:表示当前未放满的集合中的数的大小
        std::vector<int> dp((1 << n), -1);
        dp[0] = 0;

        for (int s = 1; s < (1 << n); ++s)
        {
            for (int i = 0; i < n; ++i)
            {
                // 状态s还没有使用第i个数
                if ((s & (1 << i)) == 0)
                {
                    continue;
                }

                // s1与s的区别仅在于s没有使用第i个数
                int s1 = s & ~(1 << i);
                if (dp[s1] >= 0 && (dp[s1] + nums[i] <= size))
                {
                    dp[s] = (dp[s1] + nums[i]) % size;
                    break;
                }
            }
        }

        return dp[(1 << n) - 1] == 0;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
