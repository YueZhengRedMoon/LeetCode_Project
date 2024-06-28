#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

// 记忆化搜索
class Solution
{
public:
    int paintWalls(std::vector<int>& cost, std::vector<int>& time)
    {
        const int inf = 0x3f3f3f3f;
        int n = cost.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(n + 1, - 1));    // -1表示没有计算过
        std::function<int(int, int)> dfs = [&](int i, int j) -> int
        {
            if (j <= 0)
                return 0;
            if (i < 0)
                return inf;

            int& res = memo[i][j];
            if (res != -1)
                return res;

            return res = std::min(dfs(i - 1, j - time[i] - 1) + cost[i], dfs(i - 1, j));
        };
        return dfs(n - 1, n);
    }
};

// 递推
class Solution2
{
public:
    int paintWalls(std::vector<int>& cost, std::vector<int>& time)
    {
        const int inf = 0x3f3f3f3f;
        int n = cost.size();
        std::vector<int> f(n + 1, inf);
        f[0] = 0;
        for (int i = 0; i < n; ++i)
        {
            int c = cost[i], t = time[i] + 1;
            for (int j = n; j > 0; --j)
                f[j] = std::min(f[j], f[std::max(j - t, 0)] + c);
        }
        return f[n];
    }
};

namespace TimeLimit
{
    class Solution
    {
    public:
        int paintWalls(std::vector<int>& cost, std::vector<int>& time)
        {
            int n = cost.size();

            if (n == 1)
                return cost[0];

            const int inf = 0x3f3f3f3f;
            int timeSum = std::accumulate(time.begin(), time.end(), 0);
            // f[i][j][k]:付费的油漆匠刷[0, i]号墙，工作j单位的时间，刷k堵墙所需的最小开销
            int ans = inf;
            std::vector<std::vector<std::vector<int>>> f(2, std::vector<std::vector<int>>(timeSum + 1, std::vector<int>(n + 1, inf)));
            f[0][time[0]][1] = cost[0];
            f[0][0][0] = 0;
            int maxTime = time[0];
            for (int i = 1; i < n; ++i)
            {
                int cur = i % 2, last = (i - 1) % 2;
                maxTime += time[i];
                f[cur][0][0] = 0;
                for (int j = 1; j <= maxTime; ++j)
                {
                    for (int k = 1; k <= i + 1; ++k)
                    {
                        if (j >= time[i])
                            f[cur][j][k] = std::min(f[last][j - time[i]][k - 1] + cost[i], f[last][j][k]);
                        else
                            f[cur][j][k] = f[last][j][k];
                        if (k + j >= n && f[cur][j][k] < ans)
                            ans = f[cur][j][k];
                    }
                }
            }
            return ans;
        }
    };
}

int main()
{
    Solution solution;
    std::vector<int> cost = {76,25,96,46,85,19,29,88,2,5}, time = {1,2,1,3,1,3,3,3,2,1};
    int ans = solution.paintWalls(cost, time);
    std::cout << ans << std::endl;
    return 0;
}
