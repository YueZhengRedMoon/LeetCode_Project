#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    int minOperationsMaxProfit(std::vector<int> &customers, int boardingCost, int runningCost)
    {
        int ans = -1, maxProfit = 0, profit = 0, waiting = 0, n = customers.size();
        for (int i = 0; i < n; ++i)
        {
            waiting += customers[i];                            // 新的一批游客到达
            int passenger = std::min(waiting, 4);               // 登上摩天轮的游客数
            waiting -= passenger;                               // 等候的游客数减少
            profit += passenger * boardingCost - runningCost;   // 计算利润
            logObj(profit);
            if (profit > maxProfit)
            {
                maxProfit = profit;
                ans = i + 1;
            }
        }
        // 处理剩下的游客
        logObj(waiting);
        if (waiting > 0)
        {
            int count = (waiting + 3) / 4;  // 服务剩下的所有游客还需要轮转多少次]
            int newProfit = profit + boardingCost * 4 * (count - 1) - runningCost * (count - 1);
            if (newProfit > maxProfit)
            {
                maxProfit = newProfit;
                ans = n + count - 1;
                logObj(newProfit);
            }

            newProfit = profit + boardingCost * waiting - runningCost * count;
            logObj(newProfit);
            if (newProfit > maxProfit)
            {
                ans = n + count;
            }
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> customers = {10,10,1,0,0};
    int boardingCost = 4;
    int runningCost = 4;
    int ans = solution.minOperationsMaxProfit(customers, boardingCost, runningCost);
    logObj(ans);
    return 0;
}
