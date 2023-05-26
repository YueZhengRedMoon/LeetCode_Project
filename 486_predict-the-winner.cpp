#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>

class Solution
{
public:
    bool PredictTheWinner(std::vector<int> &nums)
    {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        target = (sum + 1) / 2;
        return backtracking(nums, 0, n - 1, 0);
    }

private:
    int target;

    bool backtracking(std::vector<int> &nums, int left, int right, int curScore)
    {
        if (curScore >= target)
        {
            return true;
        }
        else if (left == right)
        {
            return curScore + nums[left] >= target;
        }
        else if (left > right)
        {
            return false;
        }
        bool chooseLeft = backtracking(nums, left + 1, right - 1, curScore + nums[left])
                          && backtracking(nums, left + 2, right, curScore + nums[left]);
        if (chooseLeft)
        {
            return true;
        }

        bool chooseRight = backtracking(nums, left + 1, right - 1, curScore + nums[right])
                           && backtracking(nums, left, right - 2, curScore + nums[right]);
        if (chooseRight)
        {
            return true;
        }

        return false;
    }
};

class Solution2
{
public:
    bool PredictTheWinner(std::vector<int> &nums)
    {
        int n = nums.size();
        // dp[i][j]:当数组剩下的部分为下标i到下标j时，当前一个玩家与另一个玩家的分数相差的最大值
        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i)
        {
            dp[i][i] = nums[i];
        }
        for (int i = n - 2; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                dp[i][j] = std::max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }
        return dp[0][n - 1] >= 0;
    }
};

int main()
{
    Solution solution;
    std::cout << std::boolalpha;
    std::vector<int> nums = {1, 5, 2};
    bool ans = solution.PredictTheWinner(nums);
    std::cout << ans << std::endl;
    return 0;
}