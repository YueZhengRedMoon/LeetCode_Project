#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int longestArithSeqLength(std::vector<int> &nums)
    {
        // 找到nums中的最大值和最小值
        auto [minIt, maxIt] = std::minmax_element(nums.begin(), nums.end());
        int diff = *maxIt - *minIt;

        int ans = 1;
        /** dp[i][d][num]:nums[0:i]中以num结尾的公差为d的等差序列的最大长度
         *  dp[i][d][num]=1表示状态无效，不存在nums[0:i]中可以构成以num结尾公差为d的等差序列
         *  对于dp[i][d][num]有2种情况:
         *  (1)不将nums[i]加入等差序列，此时dp[i][d][num] = dp[i-1][d][num]
         *  (2)将nums[i]加入等差序列，此时有两种情况:
         *      a.等差数列的长度至少为2，此时dp[i][d][num] = dp[i-1][d][num-d],
         *        其中num-d必须在区间[min-max, max-min]之间,且dp[i-1][d][num-d]必须是有效的
         *      b.等差数列的长度为1，此时dp[i][d][num] = 1
         */
        std::vector<int> dp(*maxIt + 1);
        for (int d = -diff; d <= diff; ++d) // 公差的范围只能在[min-max, max-min]
        {
            // 枚举每一种公差d的情况，由于不同公差的结果是互不影响，所以可以省去[d]这一维，且新的一轮开始时，要重置状态
            std::fill(dp.begin(), dp.end(), -1);

            // 由于dp[i][num]的值仅于dp[i-1][num]和dp[i-1][num-d]有关，所以dp数组可以压缩为一维
            for (int num : nums)
            {
                // 如果当前数为num，公差为d，则等差数量中前一个数为num-d
                int prev = num - d;

                // 前一个数在合法的范围内且存在以前一个数为结尾公差为d的状态
                if (prev >= *minIt && prev <= *maxIt && dp[prev] != -1)
                {
                    dp[num] = std::max(dp[num], dp[prev] + 1);
                    ans = std::max(ans, dp[num]);   // 记录最长等差数列序列
                }

                // 考虑等差序列长度为1的情况
                dp[num] = std::max(dp[num], 1);
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
