#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    struct OneCount
    {
        int left;
        int up;
        int leftUp;
        int rightUp;

        int max()
        {
            return std::max({left, up, leftUp, rightUp});
        }
    };

    int longestLine(std::vector<std::vector<int>> &mat)
    {
        int m = mat.size(), n = mat[0].size();
        int ans = 0;
        std::vector<std::vector<OneCount>> dp(2, std::vector<OneCount>(n, {0, 0, 0, 0}));
        if (mat[0][0] == 1)
        {
            dp[0][0] = {1, 1, 1, 1};
            ans = 1;
        }
        for (int j = 1; j < n; ++j)
        {
            if (mat[0][j] == 1)
            {
                dp[0][j] = {dp[0][j - 1].left + 1, 1, 1, 1};
                ans = std::max(ans, dp[0][j].left);
            }
        }
        printLine(dp[0]);

        for (int i = 1; i < m; ++i)
        {
            int cur = i % 2, last = (i - 1) % 2;
            for (int j = 0; j < n; ++j)
            {
                if (mat[i][j] == 1)
                {
                    // 左 & 左上
                    if (j >= 1)
                    {
                        dp[cur][j].left = dp[cur][j - 1].left + 1;
                        dp[cur][j].leftUp = dp[last][j - 1].leftUp + 1;
                    }
                    else
                    {
                        dp[cur][j].left = 1;
                        dp[cur][j].leftUp = 1;
                    }
                    // 上
                    dp[cur][j].up = dp[last][j].up + 1;
                    // 右上
                    if (j < n - 1)
                    {
                        dp[cur][j].rightUp = dp[last][j + 1].rightUp + 1;
                    }
                    else
                    {
                        dp[cur][j].rightUp = 1;
                    }
                    ans = std::max(ans, dp[cur][j].max());
                }
                else
                {
                    dp[cur][j] = {0, 0, 0, 0};
                }
            }
            printLine(dp[cur]);
        }

        return ans;
    };

private:
    void printLine(std::vector<OneCount> &line)
    {
        for (auto &cnt : line)
        {
            std::cout << "(" << cnt.left << ", " << cnt.up << ", " << cnt.leftUp << ", " << cnt.rightUp << ") ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> mat = {{1,1,0,0,1,0,0,1,1,0},
                                         {1,0,0,1,0,1,1,1,1,1},
                                         {1,1,1,0,0,1,1,1,1,0},
                                         {0,1,1,1,0,1,1,1,1,1},
                                         {0,0,1,1,1,1,1,1,1,0},
                                         {1,1,1,1,1,1,0,1,1,1},
                                         {0,1,1,1,1,1,1,0,0,1},
                                         {1,1,1,1,1,0,0,1,1,1},
                                         {0,1,0,1,1,0,1,1,1,1},
                                         {1,1,1,0,1,0,1,1,1,1}};
    int ans = solution.longestLine(mat);
    std::cout << ans << std::endl;
    return 0;
}
