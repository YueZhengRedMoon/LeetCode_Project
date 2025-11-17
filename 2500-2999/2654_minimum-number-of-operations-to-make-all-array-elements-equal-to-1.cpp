#include <iostream>
#include <vector>
#include <numeric>

class Solution
{
public:
    int minOperations(std::vector<int>& nums)
    {
        int n = nums.size(), gcdAll = 0, cnt1 = 0;  // gcdAll初始化为0，对于std::gcd，当其中一个参数为0时，会返回另一个参数
        for (int x : nums)
        {
            gcdAll = std::gcd(gcdAll, x);
            if (x == 1)
                ++cnt1;
        }

        if (gcdAll > 1)
            return -1;

        if (cnt1)
            return n - cnt1;

        // nums中没有1，需要通过操作得到一个1
        int minSize = n;    // 最小的GCD=1的子数组的长度
        for (int i = 0; i < n; ++i) // 枚举子数组左端点
        {
            int g = 0;
            for (int j = i; j < n; ++j) // 枚举子数组右端点
            {
                g = std::gcd(g, nums[j]);
                if (g == 1) // 找到GCD=1的子数组
                {
                    minSize = std::min(minSize, j - i + 1);
                    break;
                }
            }
        }

        // 通过minSize-1次操作最小的GCD=1的子数组来得到一个1，然后通过n-1次操作将整个数组变为1
        // 既minSize-1 + n-1
        return minSize + n - 2;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}