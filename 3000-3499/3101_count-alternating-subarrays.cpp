#include <iostream>
#include <vector>

class Solution
{
public:
    long long countAlternatingSubarrays(std::vector<int>& nums)
    {
        long long ans = 0;
        int n = nums.size();
        int j = 0;  // 当前交替子数组的第一个元素的索引
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] == nums[i - 1])
            {
                // nums[j, i-1]是交替子数组，长度为i - j
                ans += subArrayCount(i - j);
                j = i;
            }
        }
        ans += subArrayCount(n - j);
        return ans;
    }

private:
    // 长度为n的数组的子数组的个数
    long long subArrayCount(long long n)
    {
        return (1 + n) * n / 2;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
