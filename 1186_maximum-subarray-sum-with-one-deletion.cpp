#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maximumSum(std::vector<int> &arr)
    {
        int n = arr.size();
        int ans = arr[0];
        // dp[i]:以arr[i]为结尾的子数组的最大和
        std::vector<int> dp(n + 1, 0);
        dp[0] = arr[0];
        for (int i = 1; i < n; ++i)
        {
            dp[i] = std::max(dp[i - 1] + arr[i], arr[i]);
            if (dp[i] > ans)
                ans = dp[i];
        }

        // dp[i]:以arr[1]为起始元素的子数组的最大和
        for (int i = n - 1; i >= 0; --i)
        {
            dp[i] = std::max(dp[i + 1] + arr[i], arr[i]);
            if (dp[i] > ans)
                ans = dp[i];
            if (i >= 2 && arr[i - 1] < 0)   // 要删除一定是删除小于0的元素
                ans = std::max(ans, dp[i - 2] + dp[i]);
        }

        return ans;
    }
};

class Solution2
{
public:
    int maximumSum(std::vector<int> &arr)
    {
        int ans = arr[0];

        // dp[i][k]:以arr[i]结尾，删除k次的非空子数组的最大和
        // dp[0][0] = arr[0], dp[0][1] = 0
        int dp0 = arr[0], dp1 = 0;
        for (int i = 1; i < arr.size(); ++i)
        {
            // dp0:删除arr[i]
            // dp1 + arr[i]:以arr[i-1]为结尾的子数组中已经删除了元素，不删除arr[i]
            dp1 = std::max(dp0, dp1 + arr[i]);

            dp0 = std::max(dp0, 0) + arr[i];
            ans = std::max({ans, dp0, dp1});
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}