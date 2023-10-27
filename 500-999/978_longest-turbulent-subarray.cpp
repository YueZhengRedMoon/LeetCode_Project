#include <iostream>
#include <vector>

class Solution
{
public:
    int maxTurbulenceSize(std::vector<int> &arr)
    {
        int n = arr.size();
        // dp[0][i]:以arr[i]结尾的形如< > <的最长湍流子数组的长度
        // dp[1][i]:以arr[i]结尾的形如> < >的最长湍流子数组的长度
        int dp[2] = {1, 1};
        int ans = 1;
        for (int i = 1; i < n; ++i)
        {
            if (arr[i - 1] < arr[i])
            {
                if ((dp[0] + 1) % 2 == 0)
                {
                    ++dp[0];
                }
                else
                {
                    dp[0] = 2;
                }
                if ((dp[1] + 1) % 2 == 1)
                {
                    ++dp[1];
                }
                else
                {
                    dp[1] = 1;
                }
            }
            else if (arr[i - 1] > arr[i])
            {
                if ((dp[0] + 1) % 2 == 1)
                {
                    ++dp[0];
                }
                else
                {
                    dp[0] = 1;
                }
                if ((dp[1] + 1) % 2 == 0)
                {
                    ++dp[1];
                }
                else
                {
                    dp[1] = 2;
                }
            }
            else
            {
                dp[0] = 1;
                dp[1] = 1;
            }
            ans = std::max(ans, std::max(dp[0], dp[1]));
            std::cout << dp[0] << "\t" << dp[1] << std::endl;
        }

        return ans;
    }
};

class Solution2
{
public:
    int maxTurbulenceSize(std::vector<int> &arr)
    {
        int n = arr.size();
        int ans = 1;
        int left = 0, right = 0;

        while (right < n - 1)
        {
            if (left == right)
            {
                if (arr[left] == arr[left + 1])
                {
                    ++left;
                }
                ++right;
            }
            else
            {
                if (arr[right - 1] < arr[right] && arr[right] > arr[right + 1])
                {
                    ++right;
                }
                else if (arr[right - 1] > arr[right] && arr[right] < arr[right + 1])
                {
                    ++right;
                }
                else
                {
                    left = right;
                }
            }
            ans = std::max(ans, right - left + 1);
        }

        return ans;
    }
};

class Solution3
{
public:
    int maxTurbulenceSize(std::vector<int> &arr)
    {
        int ans = 1;
        int n = arr.size();
        // dp[i][0]:以arr[i]结尾，且arr[i-1] > arr[i]的湍流子数组的最大长度
        // dp[i][1]:以arr[i]结尾，且arr[i-1] < arr[i]的湍流子数组的最大长度
        int dp0 = 1, dp1 = 1;
        for (int i = 1; i < n; ++i)
        {
            if (arr[i - 1] > arr[i])
            {
                dp0 = dp1 + 1;
                dp1 = 1;
            }
            else if (arr[i - 1] < arr[i])
            {
                dp1 = dp0 + 1;
                dp0 = 1;
            }
            else
            {
                dp0 = 1;
                dp1 = 1;
            }
            ans = std::max(ans, std::max(dp0, dp1));
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> arr = {9,4,2,10,7,8,8,1,9};
    int ans = solution.maxTurbulenceSize(arr);
    std::cout << ans << std::endl;
    return 0;
}
