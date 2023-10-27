#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class Solution
{
public:
    int deleteAndEarn(std::vector<int> &nums)
    {
        std::map<int, int> numsCount;
        for (int num : nums)
        {
            ++numsCount[num];
        }
        int size = numsCount.size();

        // first:num second:出现次数
        std::vector<std::pair<int, int>> pairs(size);
        std::copy(numsCount.begin(), numsCount.end(), pairs.begin());

        if (size == 1)
        {
            return pairs[0].first * pairs[0].second;
        }

        // dp[i].first:删除nums[i]能获取的最大点数
        // dp[i].second:不删除nums[i]能获取的最大点数
        std::vector<std::pair<int, int>> dp(size);
        dp[0].first = pairs[0].first * pairs[0].second;
        dp[0].second = 0;
        if (pairs[0].first + 1 == pairs[1].first)
        {
            dp[1].first = pairs[1].first * pairs[1].second;
            dp[1].second = dp[0].first;
        }
        else
        {
            dp[1].first = dp[0].first + pairs[1].first * pairs[1].second;
            dp[1].second = dp[0].first;
        }

        for (int i = 2; i < size; ++i)
        {
            // 上一个元素与该元素相邻
            if (pairs[i - 1].first + 1 == pairs[i].first)
            {
                dp[i].first = std::max(std::max(dp[i - 2].first, dp[i - 2].second), dp[i - 1].second) + pairs[i].first * pairs[i].second;
                dp[i].second = std::max(dp[i - 1].first, dp[i - 1].second);
            }
            // 上一个元素与该元素不相邻
            else
            {
                dp[i].first = std::max(dp[i - 1].first, dp[i - 1].second) + pairs[i].first * pairs[i].second;
                dp[i].second = std::max(dp[i - 1].first, dp[i - 1].second);
            }
        }

        return std::max(dp[size - 1].first, dp[size - 1].second);
    }
};

class Solution2
{
public:
    int deleteAndEarn(std::vector<int> &nums)
    {
        int maxVal = 0;
        for (int val : nums)
        {
            if (val > maxVal)
                maxVal = val;
        }

        std::vector<int> sum(maxVal + 1, 0);
        for (int val : nums)
        {
            sum[val] += val;
        }

        return rob(sum);
    }

private:
    int rob(std::vector<int> &nums)
    {
        int size = nums.size();
        int first = nums[0], second = std::max(nums[0], nums[1]);
        for (int i = 2; i < size; ++i)
        {
            int temp = second;
            second = std::max(first + nums[i], second);
            first = temp;
        }
        return second;
    }
};

class Solution3
{
public:
    int deleteAndEarn(std::vector<int> &nums)
    {
        int n = nums.size();
        int ans = 0;
        std::sort(nums.begin(), nums.end());
        std::vector<int> sum = {nums[0]};
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] == nums[i - 1])
            {
                sum.back() += nums[i];
            }
            else if (nums[i - 1] + 1 == nums[i])
            {
                sum.push_back(nums[i]);
            }
            else
            {
                ans += rob(sum);
                sum = {nums[i]};
            }
        }
        ans += rob(sum);
        return ans;
    }

private:
    int rob(std::vector<int> &nums)
    {
        int size = nums.size();
        if (size == 1)
        {
            return nums[0];
        }

        int first = nums[0], second = std::max(nums[0], nums[1]);
        for (int i = 2; i < size; ++i)
        {
            int temp = second;
            second = std::max(first + nums[i], second);
            first = temp;
        }

        return second;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {2, 2, 3, 3, 3, 4};
    int result = solution.deleteAndEarn(nums);
    std::cout << result << std::endl;
    return 0;
}
