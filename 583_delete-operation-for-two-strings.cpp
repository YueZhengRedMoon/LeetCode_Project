#include <iostream>
#include <vector>

class Solution
{
public:
    int minDistance(std::string word1, std::string word2)
    {
        // dp[i][j]:以word1[i-1]结尾的子串和以word2[j-1]结尾的子串的最长公共子序列的长度
        std::vector<std::vector<int>> dp(word1.size() + 1, std::vector<int>(word2.size() + 1, 0));

        for (int i = 1; i <= word1.size(); ++i)
        {
            for (int j = 1; j <= word2.size(); ++j)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int lcsLength = dp[word1.size()][word2.size()];
        return (word1.size() - lcsLength) + (word2.size() - lcsLength);
    }
};

class Solution2
{
public:
    int minDistance(std::string word1, std::string word2)
    {
        // dp[i][j]:以word1[i-1]结尾的子串和以word2[j-1]结尾的子串最少要删除多少个字符才能相同
        std::vector<std::vector<int>> dp(word1.size() + 1, std::vector<int>(word2.size() + 1, 0));

        // 初始化
        for (int i = 0; i <= word1.size(); ++i)
            dp[i][0] = i;
        for (int j = 0; j <= word2.size(); ++j)
            dp[0][j] = j;

        for (int i = 1; i <= word1.size(); ++i)
        {
            for (int j = 1; j <= word2.size(); ++j)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + 1;
                }
            }
        }

        return dp[word1.size()][word2.size()];
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
