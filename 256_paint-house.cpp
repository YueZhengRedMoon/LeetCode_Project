#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minCost(std::vector<std::vector<int>> &costs)
    {
        // dp[i][j]:将i号房子染成j号颜色的最小花费
        int dp[2][3];
        dp[0][0] = costs[0][0];
        dp[0][1] = costs[0][1];
        dp[0][2] = costs[0][2];

        int houseNum = costs.size();
        for (int i = 1; i < houseNum; ++i)
        {
            int cur = i % 2, last = (i - 1) % 2;
            dp[cur][0] = std::min(dp[last][1], dp[last][2]) + costs[i][0];
            dp[cur][1] = std::min(dp[last][0], dp[last][2]) + costs[i][1];
            dp[cur][2] = std::min(dp[last][0], dp[last][1]) + costs[i][2];
        }
        int end = (houseNum - 1) % 2;
        return std::min({dp[end][0], dp[end][1], dp[end][2]});
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
