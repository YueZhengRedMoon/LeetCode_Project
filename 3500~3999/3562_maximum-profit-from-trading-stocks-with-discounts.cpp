#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    int maxProfit(int n, std::vector<int>& present, std::vector<int>& future,
                  std::vector<std::vector<int>>& hierarchy, int budget)
    {
        // 建图
        std::vector<std::vector<int>> g(n);
        for (const std::vector<int>& e : hierarchy)
        {
            int x = e[0] - 1, y = e[1] - 1;
            g[x].push_back(y);
        }

        std::function<std::vector<std::array<int, 2>>(int)> dfs = [&](int x) -> std::vector<std::array<int, 2>> {
            // 计算从x的所有的儿子子树y中，能够得到的最大利润之和（x不买， x买）
            std::vector<std::array<int, 2>> subF(budget + 1);
            for (int y : g[x])
            {
                std::vector<std::array<int, 2>> fy = dfs(y);
                for (int j = budget; j >= 0; --j)
                {
                    // 枚举子树y的预算为jy，当作一个体积为jy，价值为fy[jy][k]的物品
                    for (int jy = 0; jy <= j; ++jy)
                    {
                        for (int k = 0; k <= 1; ++k)
                        {
                            subF[j][k] = std::max(subF[j][k], subF[j - jy][k] + fy[jy][k]);
                        }
                    }
                }
            }

            // 计算从子树x中，能得到的最大利润之和（x父节点不买，x父节点买）
            std::vector<std::array<int, 2>> f(budget + 1);
            for (int j = 0; j <= budget; ++j)
            {
                for (int k = 0; k <= 1; ++k)    // k=0表示x父节点不买，k=1表示x父节点买
                {
                    int cost = present[x] / (k + 1);
                    if (j >= cost)
                    {
                        // 不买x，转移来源是subF[j][0]
                        // 买x，转移来源为subF[j-cost][1]，因为对于子树来说，父节点一定买
                        f[j][k] = std::max(subF[j][0], subF[j - cost][1] + future[x] - cost);
                    }
                    else    // 只能不买x
                    {
                        f[j][k] = subF[j][0];
                    }
                }
            }
            return f;
        };

        return dfs(0)[budget][0];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}