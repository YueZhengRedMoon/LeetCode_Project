#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include "../debug.h"

class Solution
{
public:
    int numTilePossibilities(std::string tiles)
    {
        std::bitset<7> used;
        backtracking(tiles, "", used);
        return sequences.size() - 1;    // 减去空串
    }

private:
    std::unordered_set<std::string> sequences;

    void backtracking(std::string &tiles, std::string sequence, std::bitset<7> &used)
    {
        if (!sequences.insert(sequence).second)
        {
            return;
        }

        for (int i = 0; i < tiles.size(); ++i)
        {
            if (!used[i])
            {
                used[i] = true;
                backtracking(tiles, sequence + tiles[i], used);
                used[i] = false;
            }
        }
    }
};

class Solution2
{
public:
    int numTilePossibilities(std::string tiles)
    {
        // 统计每种字符的数量
        std::unordered_map<char, int> count;
        for (char c : tiles)
            ++count[c];
        int kind = count.size();    // 字符的种数

        // c[i][j]:从i个数中取出j个数有多少种取法
        std::vector<std::vector<int>> c(MAX_N, std::vector<int>(MAX_N, 0));
        // 计算组合数
        calcC(c);

        int n = tiles.size();
        // dp[i][j]:从前i种字符中可以构成多少种长度为j的序列
        std::vector<std::vector<int>> dp(kind + 1, std::vector<int>(n + 1, 0));
        dp[0][0] = 1;   // 构建空串的方案数为1
        int i = 1;
        for (auto it = count.begin(); it != count.end(); ++it)
        {
            for (int j = 0; j <= n; ++j)  // 枚举序列长度
            {
                for (int k = 0; k <= std::min(it->second, j); ++k)  // 枚举选取的字符数
                {
                    // 要从i种字符中构建长度为j的字符串
                    // 则从j个位置中挑选出k个位置放第i种数，然后剩下的位置放i-1种字符构成的长度为k的序列
                    dp[i][j] += dp[i - 1][j - k] * c[j][k];
                }
            }
            ++i;
        }

        debug::printVector2D(dp);
        int ans = std::accumulate(dp[kind].begin() + 1, dp[kind].end(), 0);
        return ans;
    }

private:
    const int MAX_N = 8;

    void calcC(std::vector<std::vector<int>> &c)
    {
        int n = c.size();
        for (int i = 0; i < n; ++i)
        {
            c[i][0] = 1;
            c[i][i] = 1;
            for (int j = 1; j < i; ++j)
            {
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            }
        }
    }
};

int main()
{
    Solution2 solution;
    std::string tiles = "AAABBC";
    int ans = solution.numTilePossibilities(tiles);
    std::cout << ans << std::endl;
    return 0;
}