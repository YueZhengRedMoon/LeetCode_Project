#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

class Solution
{
public:
    int minCost(int maxTime, std::vector<std::vector<int>>& edges, std::vector<int>& passingFees)
    {
        const int inf = 0x3f3f3f3f;
        int n = passingFees.size();
        // f[t][i]:使用恰好t分钟到达城市i需要的最少通行费总和
        std::vector<std::vector<int>> f(maxTime + 1, std::vector<int>(n, inf));
        f[0][0] = passingFees[0];   // 一开始在城市0需要付通行费passingFees[0]

        for (int t = 1; t <= maxTime; ++t)
        {
            for (const std::vector<int>& edge : edges)
            {
                int i = edge[0], j = edge[1], cost = edge[2];
                if (cost <= t)
                {
                    f[t][i] = std::min(f[t][i], f[t - cost][j] + passingFees[i]);
                    f[t][j] = std::min(f[t][j], f[t - cost][i] + passingFees[j]);
                }
            }
        }

        int ans = inf;
        for (int t = 1; t <= maxTime; ++t)
        {
            ans = std::min(ans, f[t][n - 1]);
        }
        return ans == inf ? -1 : ans;
    }
};

namespace WrongAnswer
{
    class Solution
    {
    public:
        int minCost(int maxTime, std::vector<std::vector<int>>& edges, std::vector<int>& passingFees)
        {
            int n = passingFees.size();
            // 建图
            std::vector<std::unordered_map<int, int>> g(n);
            for (const std::vector<int>& e : edges)
            {
                int x = e[0], y = e[1], time = e[2];
                auto it = g[x].find(y);
                if (it == g[x].end() || it->second > time)
                {
                    g[x][y] = time;
                    g[y][x] = time;
                }
            }

            // 记忆化数组，=-1表示没计算过, =-2表示不可能
            std::vector<std::vector<int>> memo(n, std::vector<int>(maxTime + 1, -1));

            // dfs(x, t):在时间不超过t的情况下，从城市0到达城市x所需的最小费用
            std::function<int(int, int)> dfs = [&](int x, int t) -> int {
                if ((x != 0 && t <= 0) || (x == 0 && t < 0))
                    return memo[x][t] = -2;

                if (memo[x][t] != -1)
                    return memo[x][t];

                if (x == 0)
                    return memo[x][t] = passingFees[x];

                int& res = memo[x][t];
                for (auto it = g[x].begin(); it != g[x].end(); ++it)
                {
                    int y = it->first, time = it->second;
                    int res2 = dfs(y, t - time);
                    if (res2 == -2)
                        continue;

                    res = std::min(res, res2 + passingFees[x]);
                }

                return res;
            };

            return std::max(dfs(n - 1, maxTime), -1);
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
