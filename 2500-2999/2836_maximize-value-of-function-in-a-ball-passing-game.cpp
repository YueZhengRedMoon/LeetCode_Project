#include <iostream>
#include <vector>
#include <functional>
#include <unordered_set>
#include "../debug.h"

class Solution
{
public:
    long long getMaxFunctionValue(std::vector<int> &receiver, long long k)
    {
        int n = receiver.size();
        int m = 64 - __builtin_clzll(k);    // k的二进制长度
        // pa[i][j]:从玩家j开始，传2^i次球后传到的玩家以及得到的分数
        std::vector<std::vector<std::pair<int, long long>>> pa(m, std::vector<std::pair<int, long long>>(n));
        for (int i = 0; i < n; ++i)
        {
            // 从玩家i开始，传递1次球能传到的玩家及得到的分数
            pa[0][i] = {receiver[i], receiver[i]};
        }

        for (int i = 0; i < m - 1; ++i)
        {
            for (int x = 0; x < n; ++x)
            {
                auto [p, s] = pa[i][x];         // 从x开始传递2^i次球后所能到达的玩家(p)以及得到的分数(s)
                auto [pp, ss] = pa[i][p];       // 从p开始传递2^i次球后所能到达的玩家(pp)以及得到的分数(ss)
                pa[i + 1][x] = {pp, s + ss};    // 从x开始传递2^(i+1)次球后所能到达的玩家(pp)以及得到的分数(s+ss)
            }
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            long long sum = i;
            int x = i;
            for (long long t = k; t; t &= t - 1)
            {
                auto [p, s] = pa[__builtin_ctzll(t)][x];
                sum += s;
                x = p;
            }
            if (sum > ans)
                ans = sum;
        }

        return ans;
    }
};

// 超时，错误
class Solution2
{
public:
    long long getMaxFunctionValue(std::vector<int> &receiver, long long k)
    {
        int n = receiver.size();
        std::vector<std::vector<std::pair<int, long long>>> f(n); // f[i][j]:从i号玩家开始传球j次能够传到的玩家以及分数

        std::function<void(int, std::unordered_set<int>&)> dfs = [&](int p, std::unordered_set<int> &visited)
        {
            visited.insert(p);

            for (int prev : visited)
            {
                if (f[prev].empty())
                {
                    f[prev].emplace_back(p, p);
                }
                else
                {
                    f[prev].emplace_back(p, f[prev].back().second + p);
                }
            }

            int next = receiver[p];
            if (f[next].empty())
            {
                dfs(next, visited);
            }
            else if (visited.find(next) == visited.end())
            {
                for (int prev : visited)
                {
                    long long base = f[prev].back().second;
                    for (auto [id, score] : f[next])
                    {
                        f[prev].emplace_back(id, base + score);
                    }
                }
            }
        };

        for (int i = 0; i < n; ++i)
        {
            if (f[i].empty())
            {
                std::unordered_set<int> visited;
                dfs(i, visited);
            }
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            long long step = 0;
            long long score = 0;
            int cur = i;
            while (step < k)
            {
                if (receiver[cur] == cur)
                {
                    score += (k - step) * cur;
                    break;
                }

                int curMaxStep = f[cur].size() - 1;
                if (step + curMaxStep <= k)
                {
                    step += curMaxStep;
                    score += f[cur].back().second;
                    cur = receiver[f[cur].back().first];
                }
                else
                {
                    long long remain = k - step;
                    score += f[cur][remain].second;
                    break;
                }
            }
            if (score > ans)
                ans = score;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> receiver = {2,0,1};
    long long k = 4;
    long long ans = solution.getMaxFunctionValue(receiver, k);
    logObj(ans);
    return 0;
}
