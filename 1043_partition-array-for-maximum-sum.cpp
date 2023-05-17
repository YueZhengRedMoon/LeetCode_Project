#include <iostream>
#include <vector>
#include <cmath>

class Solution
{
public:
    int maxSumAfterPartitioning(std::vector<int> &arr, int k)
    {
        int n = arr.size();
        // dp[i]:将arr[0:i]划分若干个长度最多为k的子数组的元素最大和
        std::vector<int> dp(n + 1, -1);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i)
        {
            int max = -1;
            for (int j = i; j >= 1 && i - j < k; --j)
            {
                max = std::max(max, arr[j - 1]);
                dp[i] = std::max(dp[i], dp[j - 1] + max * (i - j + 1));
            }
        }

        return dp[n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
