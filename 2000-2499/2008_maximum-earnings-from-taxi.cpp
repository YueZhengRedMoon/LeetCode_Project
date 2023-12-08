#include <iostream>
#include <vector>
#include <unordered_map>
#include "debug.h"

class Solution
{
public:
    long long maxTaxiEarnings(int n, std::vector<std::vector<int>> &rides)
    {
        std::unordered_map<int, std::vector<int>> endIndices;
        for (int i = 0; i < rides.size(); ++i)
        {
            endIndices[rides[i][1]].push_back(i);
        }

        std::vector<long long> dp(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            dp[i] = dp[i - 1];
            auto it = endIndices.find(i);
            if (it == endIndices.end())
                continue;

            std::vector<int> &indices = it->second;
            for (int idx : indices)
            {
                long long start = rides[idx][0], end = rides[idx][1], tip = rides[idx][2];
                dp[i] = std::max(dp[i], dp[start] + end - start + tip);
            }
        }
        debug::printVector(dp);

        return dp[n];
    }
};

int main()
{
    Solution solution;
    int n = 10;
    std::vector<std::vector<int>> riders = {{9,10,2},{4,5,6},{6,8,1},{1,5,5},{4,9,5},
                                            {1,6,5},{4,8,3},{4,7,10},{1,9,8},{2,3,5}};
    long long ans = solution.maxTaxiEarnings(n, riders);
    logObj(ans);
    return 0;
}
