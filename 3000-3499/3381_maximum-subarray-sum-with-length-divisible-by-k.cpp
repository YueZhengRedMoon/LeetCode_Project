#include <iostream>
#include <vector>
#include <climits>

class Solution
{
public:
    long long maxSubarraySum(std::vector<int>& nums, int k)
    {
        int n = nums.size();
        std::vector<long long> s(n + 1, 0); // 前缀和数组
        for (int i = 0; i < n; ++i)
        {
            s[i + 1] = s[i] + nums[i];
        }
        // 子数组nums[i, j)的元素和为是s[j]-s[i]，长度为j - i
        // 问题等价于计算最大的s[j]-s[i]，满足j-i是k的倍数
        // 枚举j，要使s[j]-s[i]尽量大，s[i]要尽量小

        // minS[i]:i%k == j%k的s[i]最小值，例如当j=7, k=3时,只需考虑s[1], s[4]的最小值
        std::vector<long long> minS(k, LLONG_MAX / 2);
        long long ans = LLONG_MIN;
        for (int j = 0; j <= n; ++j)
        {
            int i = j % k;
            ans = std::max(ans, s[j] - minS[i]);
            minS[i] = std::min(minS[i], s[j]);
        }
        return ans;
    }
};

class Solution2
{
public:
    long long maxSubarraySum(std::vector<int>& nums, int k)
    {
        // minS[i]:i%k == j%k的s[i]最小值，例如当j=7, k=3时,只需考虑s[1], s[4]的最小值
        std::vector<long long> minS(k, LLONG_MAX / 2);
        minS[k - 1] = 0;    // 等价于初始化s[-1]=0

        long long ans = LLONG_MIN, s = 0;
        for (int j = 0; j < nums.size(); ++j)   // 前缀和的下标从-1开始
        {
            s += nums[j];
            int i = j % k;
            ans = std::max(ans, s - minS[i]);
            minS[i] = std::min(minS[i], s);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}