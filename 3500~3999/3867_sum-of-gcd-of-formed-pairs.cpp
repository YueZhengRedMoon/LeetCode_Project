#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution
{
public:
    long long gcdSum(std::vector<int>& nums)
    {
        int n = nums.size(), mx = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > mx)
                mx = nums[i];
            nums[i] = std::gcd(nums[i], mx);
        }
        std::sort(nums.begin(), nums.end());
        long long ans = 0;
        for (int i = 0, j = n - 1; i < j; ++i, --j)
        {
            ans += std::gcd(nums[i], nums[j]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}