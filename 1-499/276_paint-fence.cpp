#include <iostream>
#include <vector>

class Solution
{
public:
    int numWays(int n, int k)
    {
        if (n == 1)
        {
            return k;
        }
        // dp[i]:给第i个栅栏上色的方案数
        std::vector<int> dp(n + 1, 0);
        dp[1] = k;
        dp[2] = k * k;
        for (int i = 3; i <= n; ++i)
        {
            // (1)与上一个颜色不同：
            // dp[i-1] * (k-1)
            // (2)与上一个颜色相同，与上上个颜色不相同，当前栅栏和上一个栅栏可以看作是同一个栅栏，此时又回到了(1)式
            // dp[i-2] * (k-1)
            dp[i] = (dp[i - 1] + dp[i - 2]) * (k - 1);
        }
        return dp[n];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
