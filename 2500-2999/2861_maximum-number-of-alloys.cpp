#include <iostream>
#include <vector>
#include <numeric>
#include "../debug.h"

class Solution
{
public:
    int maxNumberOfAlloys(int n, int k, int budget,
                          std::vector<std::vector<int>>& composition, std::vector<int>& stock, std::vector<int>& cost)
    {
        int ans = 0, costSum = std::accumulate(cost.begin(), cost.end(), 0);
        for (const std::vector<int> &comp : composition)
        {
            int max = 0;
            for (int i = 0; i < n; ++i)
            {
                max = std::max(max, stock[i] / comp[i]);
            }
            int left = 0, right = max + budget / costSum;
            int cnt = 0;
            while (left < right)
            {
                long long budgetRemain = budget;
                int mid = left + (right - left) / 2;
                bool success = true;
                for (int i = 0; i < n; ++i)
                {
                    long long need = (long long) mid * comp[i];
                    if (need > stock[i])
                    {
                        budgetRemain -= cost[i] * (need - stock[i]);
                        if (budgetRemain < 0)
                        {
                            success = false;
                            break;
                        }
                    }
                }
                if (success)
                {
                    cnt = mid;
                    left = mid + 1;
                }
                else
                {
                    right = mid;
                }
            }
            if (cnt > ans)
                ans = cnt;
        }
        return ans;
    }
};

// 超时
class Solution2
{
public:
    int maxNumberOfAlloys(int n, int k, int budget,
                          std::vector<std::vector<int>>& composition, std::vector<int>& stock, std::vector<int>& cost)
    {
        int ans = 0;
        for (int i = 0; i < k; ++i)
        {
            std::vector<int> stockRemain(stock);
            int budgetRemain = budget, cnt = 0;
            while (budgetRemain > 0)
            {
                bool success = true;
                for (int j = 0; j < n; ++j)
                {
                    if (stockRemain[j] < composition[i][j])
                    {
                        budgetRemain -= cost[j] * (composition[i][j] - stockRemain[j]);
                        if (budgetRemain < 0)
                        {
                            success = false;
                            break;
                        }
                        stockRemain[j] = 0;
                    }
                    else
                    {
                        stockRemain[j] -= composition[i][j];
                    }
                }
                if (success)
                    ++cnt;
            }
            logObj(cnt);
            if (cnt > ans)
                ans = cnt;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    int n = 8, k = 4, budget = 196;
    std::vector<std::vector<int>> composition = {{5,2,3,4,7,3,3,1},
                                                 {1,5,9,9,6,1,9,7},
                                                 {5,8,3,10,2,4,8,7},
                                                 {9,9,5,9,6,8,4,3}};
    std::vector<int> stock = {3,5,3,6,1,5,8,1};
    std::vector<int> cost = {4,5,4,9,4,8,7,5};
    int ans = solution.maxNumberOfAlloys(n, k, budget, composition, stock, cost);
    logObj(ans);
    return 0;
}
