#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

/** 错误 */
class Solution
{
public:
    bool canWin(std::string state)
    {
        int n = state.size();
        // dp[i][j]:先手翻转state[i:j]是否存在必胜的方法
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        for (int i = n - 2; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (i + 1 == j)
                {
                    dp[i][j] = (state[i] == '+') && (state[j] == '+');
                    continue;
                }
                for (int k = i; k < j && !dp[i][j]; ++k)
                {
                    if (state[k] == '+' && state[k + 1] == '+')
                    {
                        if (k == i)
                        {
                            dp[i][j] = !dp[k + 2][j];
                        }
                        else if (k == j - 1)
                        {
                            dp[i][j] = !dp[i][k - 1];
                        }
                        else
                        {
                            dp[i][j] = !(dp[i][k - 1] ^ (dp[k + 2][j]));
                        }
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
};

/** 记忆化搜索 */
class Solution2
{
public:
    bool canWin(std::string state)
    {
        return backtracking(state);
    }

private:
    std::unordered_map<std::string, bool> memo;

    bool backtracking(std::string &state)
    {
        auto it = memo.find(state);
        if (it != memo.end())
            return it->second;

        int n = state.size();
        for (int i = 1; i < n; ++i)
        {
            if (state[i - 1] == '+' && state[i] == '+')
            {
                state[i - 1] = state[i] = '-';
                bool res = backtracking(state);
                state[i - 1] = state[i] = '+';
                if (!res)
                    return memo[state] = true;
            }
        }
        return memo[state] = false;
    }
};

class Solution3
{
public:
    bool canWin(std::string state)
    {
        // 记录当前输入字符串的所有子状态，一个子状态是字符串中一段连续'+'的长度
        std::vector<int> subStates;
        int len = state.size(), i = 0, j = 0;
        int max = -1;   // 最长的子状态
        // 统计给定字符串所有的子状态
        // 例如 ++--+++-+ 将得到 (2, 3, 1)
        while (i < len)
        {
            if (state[i] == '-')
            {
                ++i;
            }
            else
            {
                // 遇到了'+'，看看连续的'+'最多有多长。
                for (j = i; j < len && state[j] == '+'; ++j);
                int subState = j - i;
                subStates.push_back(subState);
                max = std::max(max, subState);
                i = j;
            }
        }
        // 输入字符串中不存在长度>=2的连续'+'子串，先手必输
        if (max <= 1)
            return false;

        // 通过动态规划计算SG函数的g值
        // Sprague-Grundy定理：
        // 如果一个节点x的g(x)=0，那么x状态一定是“先手必输”的状态，否则一定是“先手必赢”
        // 如果“游戏图”中的单个状态x可以推导出子状态{y1, y2, ……, yn}，则g(x)=mex(g(y1), g(y2),……,g(yn))
        // mex(X):集合X中第一个缺失的非负整数
        // 对于游戏的一个状态X = {x1, x2, ……, xn}，SG函数g(X)=g(x1)^(x2)^……^g(xn)
        std::vector<int> dp(max + 1, 0);
        dp[2] = 1;

        // 计算g[i]的值，获取下一步的所有状态的g值
        for (i = 3; i <= max; ++i)
        {
            // 从['+'] * i可以推出的所有状态
            std::vector<int> temp;
            // 把s[j]和s[j+1]从++变成--，连续的+变成两段，长度分别为j和i-j-2
            for (j = 0; j < i / 2; ++j)
            {
                temp.push_back(dp[j] ^ dp[i - j - 2]);
            }

            // 找到第一个缺失的非负整数
            std::sort(temp.begin(), temp.end());
            int mis = 0;
            for (int k = 0; k < temp.size(); ++k)
            {
                if (temp[k] > mis)
                    break;
                else if (temp[k] < mis)
                    continue;
                else
                    ++mis;
            }
            dp[i] = mis;
        }

        int ans = 0;
        for (int subState : subStates)
        {
            ans ^= dp[subState];
        }

        return ans;
    }
};

int main()
{
    Solution2 solution;
    std::string currentState = "++++";
    bool ans = solution.canWin(currentState);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}