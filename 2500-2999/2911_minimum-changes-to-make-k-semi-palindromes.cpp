#include <iostream>
#include <vector>
#include <functional>
#include "debug.h"

// 预处理n的所有真因子d, 真因子: 1 <= d < n并且n % d == 0
const int MAX_N = 201;
std::vector<std::vector<int>> divisors(MAX_N);
int init = []() -> int {
    for (int i = 1; i < MAX_N; ++i)
    {
        for (int j = i * 2; j < MAX_N; j += i)
        {
            divisors[j].push_back(i);
        }
    }
    return 0;
}();

// 将字符串s[begin:end]（s的长度至少为2）变成半回文串所需要的最少修改次数,O(nlogn)
int getModify(const std::string &s, int begin, int end)
{
    int n = end - begin + 1, minCnt = n;
    for (int d : divisors[n])   // 枚举字符串s的长度n的每一个真因子d, O(logn)
    {
        int cnt = 0;        // 修改次数
        for (int start = 0; start < d; ++start)
        {
            for (int i = begin + start, j = begin + n - d + start; i < j; i += d, j -= d)
            {
                cnt += (s[i] != s[j]);
            }
        }
        if (cnt < minCnt)
            minCnt = cnt;
    }
    return minCnt;
}

class Solution
{
public:

    /**
     * 划分型DP
     * dfs(i, j)
     * i 定义成剩余需要切割的次数，i+1就是切出来的子串的个数
     * j 从s[0]到s[j]是现在需要切割的部分
     * 返回值 修改的最少字符数目
     * 枚举当前这一段的左端点L
     *  - L最小是2 * i，因为半回文串的长度至少为2，如果还需要切割i次，会切出i+1个子串，
     *    去除当前得到的子串还有i个子串，即至少还需要2 * i长度来切剩下的串
     *  - L最大是j-1，即当前切出的子串为s[j-1:j]
     *  设 modify[i][j] = s[i:j]的最小修改次数
     *  dfs(i, j) <- min dfs(i-1, L-1) + modify[L][j]
     *  递归终点：i=0 return modify[0][j]
     *  递归入口：dfs(k-1, n-1)
     * */

    int minimumChanges(std::string s, int k)
    {
        int n = s.size();
        std::vector<std::vector<int>> modify(n, std::vector<int>(n));
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
                modify[i][j] = getModify(s, i, j);
        }

        std::vector<std::vector<int>> memo(n / 2 + 1, std::vector<int>(n, -1));

        std::function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (memo[i][j] != -1)
                return memo[i][j];

            if (i == 0)
                return modify[0][j];

            int res = n;
            for (int l = 2 * i; l < j; ++l)
            {
                res = std::min(res, dfs(i - 1, l - 1) + modify[l][j]);
            }
            return memo[i][j] = res;
        };

        return dfs(k - 1, n - 1);
    }
};

class Solution2
{
public:
    int minimumChanges(std::string s, int k)
    {
        int n = s.size();
        std::vector<std::vector<int>> modify(n, std::vector<int>(n));
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
                modify[i][j] = getModify(s, i, j);
        }

        // dp[i][j]:把s[0:i]的字符串分成j+1个字符串，使得每个字符串变成半回文串需要修改的最少字符数
        std::vector<int> dp(modify[0]);
        for (int i = 1; i < k; ++i) // 枚举分割的次数
        {
            // k-1-i:还能分割的次数
            for (int j = n - 1 - (k - 1 - i) * 2; j > i * 2; --j)
            {
                dp[j] = n;
                for (int l = i * 2; l < j; ++l)
                    dp[j] = std::min(dp[j], dp[l - 1] + modify[l][j]);
            }
        }

        return dp[n - 1];
    }
};

int main()
{
    Solution solution;
    std::string s = "abcac";
    int k = 2;
    int ans = solution.minimumChanges(s, k);
    logObj(ans);
    return 0;
}