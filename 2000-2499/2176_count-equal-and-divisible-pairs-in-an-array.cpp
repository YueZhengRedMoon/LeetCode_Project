#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>

const int MX = 101;
std::vector<int> divisors[MX];

auto init = [] {
    for (int i = 1; i < MX; ++i)
    {
        for (int j = i; j < MX; j += i)
        {
            divisors[j].push_back(i);
        }
    }
    return 0;
}();

class Solution
{
public:
    int countPairs(std::vector<int>& nums, int k)
    {
        int n = nums.size(), ans = 0;
        std::unordered_map<int, int> cnt;
        for (int j = 0; j < n; ++j) // 枚举j，计算左边有多少个符合要求的i
        {
            int x = nums[j];
            if (j && x == nums[0])
            {
                // 单独统计 i=0 的情况
                ++ans;
            }

            int k2 = k / std::gcd(k, j);    // i 必须是k2的倍数
            ans += cnt[k2 << 10 | x];   // 用位运算把二元组 (x, k2) 合并成一个整数
            for (int d : divisors[j])   // j是d的倍数
            {
                ++cnt[d << 10 | x];
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
