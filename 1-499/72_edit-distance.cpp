#include <iostream>
#include <vector>

class Solution
{
public:
    int minDistance(std::string word1, std::string word2)
    {
        int len1 = word1.size();
        int len2 = word2.size();
        // dp[i][j]:word1[0:i-1]变换到word[0:j-1]最少要操作多少次
        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));

        // 初始化
        for (int i = 0; i <= len1; ++i)
            dp[i][0] = i;
        for (int j = 1; j <= len2; ++j)
            dp[0][j] = j;

        // 递推公式：
        // 如果word1[i-1] == word2[j-1],则dp[i][j] = dp[i-1][j-1]      表示无需变换
        // 否则dp[i][j] = min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1
        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    // 如果是dp[i-1][j-1]是最小的，则表示替换
                    // 否则表示删除或增加
                    dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                }
            }
        }

        return dp[len1][len2];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
