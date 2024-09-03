#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

class Solution
{
public:
    long long maxStrength(std::vector<int>& nums)
    {
        int n = nums.size();
        long long ans = std::numeric_limits<long long>::min();
        std::vector<long long> f(1 << n, std::numeric_limits<long long>::min());
        f[0] = 1;
        for (int s = 1; s < (1 << n); ++s)
        {
            for (int i = 0; i < n; ++i)
            {
                if (s & (1 << i))
                {
                    f[s] = std::max(f[s], f[s & (~(1 << i))] * nums[i]);
                    if (f[s] > ans)
                        ans = f[s];
                }
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    long long maxStrength(std::vector<int>& nums)
    {
        // 从左到右遍历nums
        // mn:遍历到nums[i]时，nums[0,i]中的最小乘积
        // mx:遍历到nums[i]时，nums[0,i]中的最大乘积
        long long mn = nums[0], mx = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            long long x = nums[i], tmp = mn;
            mn = std::min({x, mn, mx * x, mn * x});
            mx = std::max({x, mx, mx * x, tmp * x});
        }
        return mx;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
