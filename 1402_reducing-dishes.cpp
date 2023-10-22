#include <iostream>
#include <vector>
#include <algorithm>
#include "debug.h"

class Solution
{
public:
    int maxSatisfaction(std::vector<int> &satisfaction)
    {
        int n = satisfaction.size(), ans = 0;
        std::sort(satisfaction.begin(), satisfaction.end());

        int sum = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            sum += satisfaction[i];
            if (sum > 0)
                ans += sum;
            else
                break;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> satisfaction = {-1, -8, 0, 5, -7};
    int ans = solution.maxSatisfaction(satisfaction);
    logObj(ans);
    return 0;
}