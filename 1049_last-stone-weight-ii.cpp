#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int lastStoneWeightII(std::vector<int> &stones)
    {
        int totalWeight = std::accumulate(stones.begin(), stones.end(), 0);
        int target = totalWeight / 2;

        // dp[j]:容量为j的背包最大能装多少价值的物品
        std::vector<int> dp(target + 1, 0);

        for (int i = 0; i < stones.size(); ++i)
        {
            for (int j = target; j >= stones[i]; --j)
            {
                dp[j] = std::max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }

        return totalWeight - dp[target] - dp[target];
    }
};

int main()
{
    std::vector<int> stones = {2, 7, 4, 1, 8, 1};
    Solution solution;
    std::cout << solution.lastStoneWeightII(stones) << std::endl;
    return 0;
}
