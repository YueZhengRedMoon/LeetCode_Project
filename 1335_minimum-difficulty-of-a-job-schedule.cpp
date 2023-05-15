#include <iostream>
#include <vector>
#include <limits>

class Solution
{
public:
    int minDifficulty(std::vector<int> &jobDifficulty, int d)
    {
        int n = jobDifficulty.size();
        if (n < d)
        {
            return -1;
        }

        const int inf = std::numeric_limits<int>::max();
        // dp[i][j]:将0~i的工作放到第0~j天做，所需的最小工作量
        std::vector<std::vector<int>> dp(n, std::vector<int>(d, inf));

        dp[0][0] = jobDifficulty[0];
        for (int i = 1; i < n; ++i)
        {
            dp[i][0] = std::max(dp[i - 1][0], jobDifficulty[i]);
        }

        for (int i = 1; i < d; ++i)
        {
            // 第j天开始最迟也得开始做第j个工作
            // 且第j天不能做太多的工作从而导致导致后面会有一天空闲
            for (int j = i; j < n && (n - j) >= (d - i); ++j)
            {

            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}