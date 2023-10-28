#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug/debug.h"

/** 错误 */
class Solution
{
public:
    int tilingRectangle(int n, int m)
    {
        // dp[i][j]:i×j大小的地板最少可以用几块正方形瓷砖铺满
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (i == j)
                {
                    dp[i][j] = 1;
                    continue;
                }
                dp[i][j] = 0x3f3f3f3f;
                for (int k = 1; k <= std::min(i, j); ++k)
                {
                    dp[i][j] = std::min({dp[i][j], 1 + dp[i - k][j] + dp[k][j - k], 1 + dp[i - k][k] + dp[i][j - k]});
                }
            }
        }
        return dp[n][m];
    }
};

class Solution2
{
public:
    int tilingRectangle(int n_, int m_)
    {
        n = n_;
        m = m_;
        floor.resize(n, std::vector<bool>(m, false));
        backtracking(0);
        return ans;
    }

private:
    std::vector<std::vector<bool>> floor;
    int n, m;
    int ans{0x3f3f3f3f};

    void backtracking(int num)
    {
        if (num >= ans)
            return;

        debug::printVector2D(floor);
        std::cout << "num = " <<  num << '\n'  << std::endl;
        int topLeftX, topLeftY;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (!floor[i][j])
                {
                    topLeftX = i;
                    topLeftY = j;
                    goto findEmpty;
                }
            }
        }
        // 执行到此处，说明房间都已经填满，更新答案
        ans = num;
        return;

        // 找到空的瓷砖，开始从大到小填充瓷砖
        findEmpty:
        int maxLen = std::min(n - topLeftX, m - topLeftY);
        // 避免出现下面这种情况，计算出正确的maxLen
        // 1 1 1 1
        // 0 0 1 1
        // 0 0 1 1
        // 0 0 1 1
        for (int i = 0; i < maxLen; ++i)
        {
            for (int j = 0; j < maxLen; ++j)
            {
                if (floor[topLeftX + i][topLeftY + j])
                {
                    maxLen = i;
                }
            }
        }
        for (int i = 0; i < maxLen; ++i)
        {
            for (int j = 0; j < maxLen; ++j)
            {
                floor[topLeftX + i][topLeftY + j] = true;
            }
        }
        for (int k = maxLen - 1; k >= 0; --k)
        {
            backtracking(num + 1);
            for (int i = 0; i < k; ++i)
                floor[topLeftX + i][topLeftY + k] = false;
            for (int j = 0; j < k; ++j)
                floor[topLeftX + k][topLeftY + j] = false;
            floor[topLeftX + k][topLeftY + k] = false;
        }
    }
};

int main()
{
    Solution2 solution;
    int ans = solution.tilingRectangle(3, 4);
    std::cout << ans << std::endl;
    return 0;
}