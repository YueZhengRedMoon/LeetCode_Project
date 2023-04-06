#include <iostream>

class Solution
{
public:
    int numTrees(int n)
    {
        // dp[i]:由i个节点组成的二叉树有多少种
        int dp[20];

        // 初始化
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; ++i)
        {
            dp[i] = 0;
            for (int j = 0; j <= (i - 1) / 2; ++j)
            {
                dp[i] += dp[j] * dp[i - 1 - j];
            }
            dp[i] *= 2;
            if ((i - 1) % 2 != 0)
            {
                dp[i] -= dp[(i - 1) / 2];
            }
        }
        for (int i = 0; i <= n; ++i)
        {
            std::cout << i << '\t';
        }
        std::cout << std::endl;
        for (int i = 0; i <= n; ++i)
        {
            std::cout << dp[i] << '\t';
        }
        std::cout << std::endl;
        return dp[n];
    }
};

int main()
{
    int n;
    std::cin >> n;
    Solution solution;
    int result = solution.numTrees(n);
    std::cout << result << std::endl;
    return 0;
}
