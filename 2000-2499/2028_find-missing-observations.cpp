#include <iostream>
#include <vector>
#include <numeric>
#include "debug.h"

class Solution
{
public:
    std::vector<int> missingRolls(std::vector<int>& rolls, int mean, int n)
    {
        int m = rolls.size();
        int sumM = std::accumulate(rolls.begin(), rolls.end(), 0), sum = mean * (m + n);
        int sumN = sum - sumM;

        if (sumN <= 0 || (sumN + 5) / 6 > n || sumN < n)
            return {};

        std::vector<int> ans(n, sumN / n);
        int r = sumN % n, i = 0;
        while (r > 0)
        {
            int x = std::min(6, ans[i] + r);
            int d = x - ans[i];
            ans[i++] = x;
            r -= d;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> rolls = {4,2,2,5,4,5,4,5,3,3,6,1,2,4,2,1,6,5,4,2,3,4,2,3,3,5,4,1,4,4,5,3,6,1,5,2,3,3,6,1,6,4,1,3};
    int mean = 2;
    int n = 53;
    std::vector<int> ans = solution.missingRolls(rolls, mean, n);
    debug::printVector(ans);
    return 0;
}
