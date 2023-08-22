#include <iostream>
#include <vector>
#include <unordered_map>
#include <forward_list>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    int maximizeTheProfit(int n, std::vector<std::vector<int>> &offers)
    {
        int offersNum = offers.size(), ans = 0;

        // 将所有房子的编号+1以便于处理
        // dp[i]出售范围在[1:i]以内的房子可以获得的最大金币数
        std::vector<int> dp(n + 1, 0);
        std::unordered_map<int, std::forward_list<int>> endMap;
        for (int i = 0; i < offersNum; ++i)
        {
            ++offers[i][0];
            ++offers[i][1];
            endMap[offers[i][1]].emplace_front(i);
        }

        for (int i = 1; i <= n; ++i)
        {
            dp[i] = dp[i - 1];
            auto endMapIt = endMap.find(i);
            if (endMapIt != endMap.end())
            {
                for (int offerId : endMapIt->second)
                {
                    dp[i] = std::max(dp[i], dp[offers[offerId][0] - 1] + offers[offerId][2]);
                }
            }
            if (dp[i] > ans)
                ans = dp[i];
        }

        debug::printVector(dp);

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> offers = {{1,2,5},{4,6,7},{0,2,4},{4,4,1},{2,4,7},{0,5,4},{2,3,7},{3,4,6},{1,2,9},{2,5,8}};
    int ans = solution.maximizeTheProfit(7, offers);
    logObj(ans);
    return 0;
}
