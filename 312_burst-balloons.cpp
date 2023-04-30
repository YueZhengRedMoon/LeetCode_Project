#include <iostream>
#include <vector>
#include <algorithm>

/** 错误，戳爆一个区间的气球所能得到的最大硬币数不止与气球内的区间有关，还与区间外的任意一个气球都有关 */
class Solution
{
public:
    int maxCoins(std::vector<int> &nums)
    {
        int size = nums.size();
        std::vector<std::vector<int>> dp(size, std::vector<int>(size, 0));

        for (int i = size - 1; i >= 0; --i)
        {
            for (int j = i; j < size; ++j)
            {
                int left = (i > 0 ? nums[i - 1] : 1);
                int right = (j < size - 1 ? nums[j + 1] : 1);
                if (i == j)
                {
                    dp[i][j] = left * nums[i] * right;
                }
                else if (i + 1 == j)
                {
                    dp[i][j] = std::max(dp[i][i] + left * nums[j] * right, dp[j][j] + left * nums[i] * right);
                }
                else
                {
                    int centerArea = dp[i + 1][j - 1] + std::max(left * nums[i] * nums[j] + left * nums[j] * right,
                                                           nums[i] * nums[j] * right + left * nums[i] * right);
                    int leftArea = dp[i][j - 1] + left * nums[j] * right;
                    int rightArea = dp[i + 1][j] + left * nums[i] * right;
                    dp[i][j] = std::max(centerArea, std::max(leftArea, rightArea));
                }
            }
        }

        return dp[0][size - 1];
    }
};

/** 记忆化搜索
 *  思想：将戳爆气球的过程逆转，变成逐渐添加气球，直到填满区间
 *  则对于一个当前区间[left, right]，要在其中添加一个气球使得能获得的硬币数最大，则先添加区间中num最大的气球
 * */
class Solution2
{
public:
    int maxCoins(std::vector<int> &nums)
    {
        int n = nums.size();
        val.resize(n + 2);
        for (int i = 1; i <= n; ++i)
        {
            val[i] = nums[i - 1];
        }
        val[0] = val[n + 1] = 1;
        rec.resize(n + 2, std::vector<int>(n + 2, -1));
        return solve(0, n + 1);
    }

private:
    std::vector<std::vector<int>> rec;
    std::vector<int> val;

    int solve(int left, int right)
    {
        if (left >= right - 1)
        {
            return 0;
        }
        if (rec[left][right] != -1)
        {
            return rec[left][right];
        }
        for (int i = left + 1; i < right; ++i)
        {
            int sum = val[left] * val[i] * val[right];
            sum += solve(left, i) + solve(i, right);
            rec[left][right] = std::max(rec[left][right], sum);
        }
        return rec[left][right];
    }
};

/** 动态规划
 *  思路同Solution2
 * */
class Solution3
{
public:
    int maxCoins(std::vector<int> &nums)
    {
        int size = nums.size();
        // dp[i][j]:填满开区间(i, j)所能获得的最大硬币数
        std::vector<std::vector<int>> dp(size + 2, std::vector<int>(size + 2, 0));

        std::vector<int> val(size + 2, 1);
        std::copy(nums.begin(), nums.end(), val.begin() + 1);

        for (int i = size - 1; i >= 0; --i)
        {
            for (int j = i + 2; j <= size + 1; ++j)
            {
                for (int k = i + 1; k < j; ++k)
                {
                    int sum = val[i] * val[k] * val[j] + dp[i][k] + dp[k][j];
                    dp[i][j] = std::max(sum, dp[i][j]);
                }
            }
        }

        return dp[0][size + 1];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
