#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int sumOfPower(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        const int mod = 1e9 + 7;
        int n = nums.size(), dp = 0, preSum = 0, ans = 0;
        for (int i = 0; i < n; ++i)
        {
            dp = (nums[i] + preSum) % mod;
            preSum = (preSum + dp) % mod;
            ans = (int) ((ans + (long long) nums[i] * nums[i] % mod * dp) % mod);
            if (ans < 0)
                ans += mod;
        }
        return ans;
    }
};

class Solution2
{
public:
    int sumOfPower(std::vector<int> &nums)
    {
        const int mod = 1e9 + 7;
        std::sort(nums.begin(), nums.end());
        int ans = 0, s = 0;
        for (long long x : nums)
        {
            ans = (ans + x * x % mod * (x + s)) % mod;
            s = (s * 2 + x) % mod;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}