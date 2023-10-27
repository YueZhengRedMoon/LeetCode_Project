#include <iostream>
#include <vector>
#include <cstring>
#include <functional>
#include <limits>
#include <algorithm>
#include <stack>
#include "../debug.h"

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

        const int inf = 0x3f3f3f3f;
        // dp[i][j]:前i+1天完成前j项工作的最小难度
        std::vector<std::vector<int>> dp(d, std::vector<int>(n, inf));

        int max = 0;
        for (int i = 0; i < n; ++i)
        {
            max = std::max(max, jobDifficulty[i]);
            dp[0][i] = max;
        }

        for (int i = 1; i < d; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                max = 0;
                for (int k = j; k >= i; --k)
                {
                    max = std::max(max, jobDifficulty[k]);
                    dp[i][j] = std::min(dp[i][j], dp[i - 1][k - 1] + max);
                }
            }
        }

        debug::printVector2D(dp, inf);

        return dp[d - 1][n - 1];
    }
};

class Solution2
{
public:
    int minDifficulty(std::vector<int> &jobDifficulty, int d)
    {
        int n = jobDifficulty.size();
        if (n < d) return -1;

        const int inf = 0x3f3f3f3f;
        // dp[i][j]:前i+1天完成工作0~工作j需要的最少难度
        std::vector<int> dp(n, inf);

        // 初始化，第1天依次完成每个工作需要的最小难度
        int max = 0;
        for (int j = 0; j < n; ++j)
        {
            max = std::max(max, jobDifficulty[j]);
            dp[j] = max;
        }

        // 遍历工作天数
        for (int i = 1; i < d; ++i)
        {
            // 遍历从第i天开始的工作任务，第i天开始时至少要开始做第i个任务
            for (int j = n - 1; j >= i; --j)
            {
                dp[j] = inf;
                max = 0;
                // 枚举从第k个任务到第j个任务中工作难度最大的任务，第k个任务到第j个任务在第i天做，前k-1个任务在前i-1天做
                for (int k = j; k >= i; --k)
                {
                    max = std::max(max, jobDifficulty[k]);
                    dp[j] = std::min(dp[j], dp[k - 1] + max);
                }
            }
        }

        return dp[n - 1];
    }
};

class Solution3
{
public:
    int minDifficulty(std::vector<int> &jobDifficulty, int d)
    {
        int n = jobDifficulty.size();
        if (n < d) return -1;

        std::vector<std::vector<int>> dp(d, std::vector<int>(n));

        dp[0][0] = jobDifficulty[0];
        for (int j = 1; j < n; ++j)
        {
            dp[0][j] = std::max(dp[0][j - 1], jobDifficulty[j]);
        }

        for (int i = 1; i < d; ++i)
        {
            // 栈顶表示第j个工作前面第一个难度大于第j个工作的难度的工作下标
            // 左边第一个难度大于j的工作left[j]，从dp[i-1][left[j]+1]到dp[i-1][j-1]的最小值
            std::stack<std::pair<int, int>> stack;
            for (int j = i; j < n; ++j)
            {
                int min = dp[i - 1][j - 1];
                while (!stack.empty() && jobDifficulty[stack.top().first] <= jobDifficulty[j])
                {
                    min = std::min(min, stack.top().second);
                    stack.pop();
                }
                dp[i][j] = min + jobDifficulty[j];
                if (!stack.empty())
                {
                    dp[i][j] = std::min(dp[i][j], dp[i][stack.top().first]);
                }
                stack.emplace(j, min);
            }
        }

        return dp[d - 1][n - 1];
    }
};

/*
class Solution2
{
public:
    int minDifficulty(std::vector<int> &jobDifficulty, int d)
    {
        int n = jobDifficulty.size();
        if (n < d) return -1;

        int memo[d][n];
        std::memset(memo, -1, sizeof(memo));    // -1表示还没有计算过
        // dfs(i, j):用前i+1天完成工作0到工作j需要的最小难度
        std::function<int(int, int)> dfs = [&](int i, int j) -> int {
            int &res = memo[i][j];

            // 之前已经计算过了
            if (res != -1)
                return res;
            // 只有一天，必须完成所有工作
            if (i == 0)
            {
                int max = 0;
                for (int k = 0; k <= j; ++k)
                {
                    max = std::max(max, jobDifficulty[k]);
                }
                return res = max;
            }

            res = std::numeric_limits<int>::max();
            int max = 0;
            for (int k = j; k >= i; --k)
            {
                max = std::max(max, jobDifficulty[k]);  // 从jobDifficulty[k]到jobDifficulty[j]的最大值
                res = std::min(res, dfs(i - 1, k - 1) + max);
            }
            return res;
        };

        return dfs(d - 1, n - 1);
    }
};
*/

int main()
{
    Solution3 solution;
    std::vector<int> jobDifficulty = {6,5,4,3,2,1};
    int d = 2;
    int result = solution.minDifficulty(jobDifficulty, d);
    std::cout << result << std::endl;

    std::vector<int> jobDifficulty2 = {11,111,22,222,33,333,44,444};
    int d2 = 6;
    int result2 = solution.minDifficulty(jobDifficulty2, d2);
    std::cout << result2 << std::endl;
    return 0;
}