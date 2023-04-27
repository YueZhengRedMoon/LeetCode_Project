#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

class Solution
{
public:
    std::string optimalDivision(std::vector<int> &nums)
    {
        if (nums.size() == 1)
            return std::to_string(nums[0]);
        std::ostringstream oss;
        oss << nums[0] << '/';
        if (nums.size() > 2)
            oss << '(';
        for (int i = 1; i < nums.size() - 1; ++i)
        {
            oss << nums[i] << '/';
        }
        oss << nums.back();
        if (nums.size() > 2)
            oss << ")";
        return oss.str();
    }
};

class Solution2
{
public:
    struct Node
    {
        double maxVal{std::numeric_limits<int>::min()};
        double minVal{std::numeric_limits<int>::max()};
        std::string minStr;
        std::string maxStr;
    };

    std::string optimalDivision(std::vector<int> &nums)
    {
        int n = nums.size();
        // dp[i][j].maxVal:通过添加括号，使得nums[i:j]能获得的最大值
        // dp[i][j].minVal:通过添加括号，使得nums[i:j]能获得的最小值
        // dp[i][j].maxStr:通过添加括号，使得nums[i:j]能获得的最大值的表达式字符串
        // dp[i][j].minStr:通过添加括号，使得nums[i:j]能获得的最小值的表达式字符串
        std::vector<std::vector<Node>> dp(n, std::vector<Node>(n));

        for (int i = 0; i < n; ++i)
        {
            dp[i][i].minVal = nums[i];
            dp[i][i].maxVal = nums[i];
            dp[i][i].minStr = std::to_string(nums[i]);
            dp[i][i].maxStr = std::to_string(nums[i]);
        }

        // 枚举区间的长度i
        for (int i = 1; i < n; ++i)
        {
            // 枚举区间的起始位置i
            for (int j = 0; j + i < n; ++j)
            {
                // 枚举区间分隔点k∈[j, j + i)来将区间分为[j, k]和[k + 1, j + i)两部分
                for (int k = j; k < j + i; ++k)
                {
                    // 区间[j, j + i)的最大值可以通过区间[j, k]的最大值除以区间[k + 1, j + i)的最小值得到
                    if (dp[j][j + i].maxVal < (dp[j][k].maxVal / dp[k + 1][j + i].minVal))
                    {
                        dp[j][j + i].maxVal = dp[j][k].maxVal / dp[k + 1][j + i].minVal;
                        if (k + 1 == j + i) // 右边区间长度为1，即只有1个数，无需加括号
                        {
                            dp[j][j + i].maxStr = dp[j][k].maxStr + "/" + dp[k + 1][j + i].minStr;
                        }
                        else
                        {
                            dp[j][j + i].maxStr = dp[j][k].maxStr + "/(" + dp[k + 1][j + i].minStr + ")";
                        }
                    }
                    // 区间[j, j + i)的最小值可以通过区间[j, k]的最小值除以区间[k + 1, j + i)的最大值得到
                    if (dp[j][j + i].minVal > (dp[j][k].minVal / dp[k + 1][j + i].maxVal))
                    {
                        dp[j][j + i].minVal = dp[j][k].minVal / dp[k + 1][j + i].maxVal;
                        if (k + 1 == j + i) // 右边区间长度为1，即只有1个数，无需加括号
                        {
                            dp[j][j + i].minStr = dp[j][k].minStr + "/" + dp[k + 1][j + i].maxStr;
                        }
                        else
                        {
                            dp[j][j + i].minStr = dp[j][k].minStr + "/(" + dp[k + 1][j + i].maxStr + ")";
                        }
                    }
                }
            }
        }

        return dp[0][n - 1].maxStr;
    }
};

int main()
{
    std::vector<int> nums = {100, 2, 30, -50, 4, 20, -10};
    Solution2 solution;
    std::cout << solution.optimalDivision(nums) << std::endl;
    return 0;
}
