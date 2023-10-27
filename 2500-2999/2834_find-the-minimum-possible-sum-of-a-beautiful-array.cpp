#include <iostream>
#include <vector>
#include "../debug.h"

class Solution
{
public:
    int minimumPossibleSum(int n, int target)
    {
        const int mod = 1e9 + 7;
        std::vector<bool> available(target, true);
        int i, j;
        long long sum = 0;
        for (i = 0, j = 1; i < n && j < target; ++j)
        {
            if (available[j])
            {
                available[target - j] = false;
                sum = (sum + j) % mod;
                ++i;
            }
        }
        if (i < n)
        {
            sum = (sum + ((target + target + n - i - 1) * (n - i) / 2) % mod) % mod;
        }
        return (int)sum;
    }
};

class Solution2
{
public:
    int minimumPossibleSum(int n, int target)
    {
        const int mod = 1e9 + 7;
        long long m = std::min(target / 2, n);
        long long ans = (((1 + m) * m / 2) % mod + ((target * 2 % mod  + n - m - 1) * (n - m) / 2) % mod) % mod;
        return (int)ans;
    }
};

int main()
{
    Solution solution;
    int ans = solution.minimumPossibleSum(39636, 49035);
    logObj(ans);
    return 0;
}
