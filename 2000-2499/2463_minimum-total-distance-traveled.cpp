#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class Solution
{
public:
    // 对于任意一对机器人 i 和 j（i<j），机器人 i 去的工厂编号 ≤ 机器人 j 去的工厂编号

    long long minimumTotalDistance(std::vector<int>& robot, std::vector<std::vector<int>>& factory)
    {
        std::sort(factory.begin(), factory.end());
        std::sort(robot.begin(), robot.end());

        int n = factory.size(), m = robot.size();
        std::vector<std::vector<long long>> memo(n, std::vector<long long>(m, -1));
        // dfs(i, j):factory[0,i]的工厂修理robot[0,j]的机器人，机器人移动的最小距离
        std::function<long long(int, int)> dfs = [&](int i, int j) -> long long {
            if (j < 0)  // 所有机器人都修完了
            {
                return 0;
            }
            if (i < 0)  // 还有机器人没修，但没有工厂了
            {
                return LLONG_MAX / 2;   // 避免加法溢出
            }

            long long& res = memo[i][j];
            if (res != -1)
            {
                return res;
            }

            // 工厂i不修机器人
            res = dfs(i - 1, j);

            int position = factory[i][0], limit = factory[i][1];
            long long disSum = 0;
            // 枚举修k个机器人，k <= min(robot[0,j]有j+1个机器人, 工厂i最多只能修limit个机器人)
            for (int k = 1; k <= std::min(j + 1, limit); ++k)
            {
                disSum += std::abs(robot[j - k + 1] - position);
                res = std::min(res, dfs(i - 1, j - k) + disSum);
            }

            return res;
        };

        return dfs(n - 1, m - 1);
    }
};

class Solution2
{
public:
    long long minimumTotalDistance(std::vector<int>& robot, std::vector<std::vector<int>>& factory)
    {
        std::sort(factory.begin(), factory.end());
        std::sort(robot.begin(), robot.end());

        int n = factory.size(), m = robot.size();
        // f[i][j]:factory[0,i)的工厂修理robot[0,j)的机器人，机器人移动的最小距离
        std::vector<std::vector<long long>> f(n + 1, std::vector<long long>(m + 1));
        std::fill(f[0].begin() + 1, f[0].end(), LLONG_MAX / 2); // 还有机器人没修，但没有工厂了
        for (int i = 0; i < n; ++i)
        {
            int position = factory[i][0], limit = factory[i][1];
            for (int j = 0; j < m; ++j)
            {
                // 工厂 i 不修机器人
                long long res = f[i][j + 1];

                // 枚举修k个机器人
                long long disSum = 0;
                for (int k = 1; k <= std::min(j + 1, limit); ++k)
                {
                    disSum += std::abs(robot[j - k + 1] - position);
                    res = std::min(res, f[i][j - k + 1] + disSum);
                }
                f[i + 1][j + 1] = res;
            }
        }

        return f[n][m];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}