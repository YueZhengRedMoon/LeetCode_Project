#include <iostream>
#include <vector>

class Solution
{
public:
    long long sumDigitDifferences(std::vector<int>& nums)
    {
        int digitLen = 0;
        for (int i = nums[0]; i; i /= 10)
            ++digitLen;

        // cnt[i][j]:第i位数是j的数的个数
        std::vector<std::vector<int>> cnt(digitLen, std::vector<int>(10, 0));
        for (int x : nums)
        {
            for (int i = 0; x; ++i, x /= 10)
            {
                ++cnt[i][x % 10];
            }
        }

        long long ans = 0, n = nums.size();
        for (int i = 0; i < digitLen; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                ans += cnt[i][j] * (n - cnt[i][j]);
            }
        }

        return ans / 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
