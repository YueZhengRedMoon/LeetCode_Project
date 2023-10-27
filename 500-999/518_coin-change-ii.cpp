#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int change(int amount, std::vector<int> &coins)
    {
        if (amount == 0)
        {
            return 0;
        }

        // dp[i]:凑成面值为i的硬币组合数
        std::vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        std::cout << "先遍历物品，后遍历背包，求出的是组合数" << std::endl;
        // 先遍历物品，后遍历背包，求出的是组合数
        for (int i = 0; i < coins.size(); ++i)
        {
            for (int j = coins[i]; j <= amount; ++j)
            {
                dp[j] += dp[j - coins[i]];
            }
            std::for_each(dp.begin(), dp.end(), [](int i) {std::cout << i << ' ';});
            std::cout << std::endl;
        }

        // 先遍历背包，后遍历物品，得到的是排列数
        std::vector<int> dp2(amount + 1, 0);
        dp2[0] = 1;
        std::cout << "先遍历背包，后遍历物品，得到的是排列数" << std::endl;
        for (int j = 0; j <= amount; ++j)
        {
            for (int i = 0; i < coins.size(); ++i)
            {
                if (j >= coins[i])
                    dp2[j] += dp2[j - coins[i]];
            }
            std::for_each(dp2.begin(), dp2.end(), [](int i) {std::cout << i << ' ';});
            std::cout << std::endl;
        }

        return dp[amount];
    }
};

int main()
{
    std::vector<int> coins = {1, 2, 5};
    int amount = 5;
    Solution solution;
    std::cout << solution.change(amount, coins) << std::endl;
    return 0;
}