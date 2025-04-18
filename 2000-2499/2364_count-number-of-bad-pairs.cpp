#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    long long countBadPairs(std::vector<int>& nums)
    {
        int n = nums.size();
        std::unordered_map<int, int> counter;
        for (int i = 0; i < n; ++i)
        {
            nums[i] = nums[i] - i;
            ++counter[nums[i]];
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans += (n - i - 1) - (--counter[nums[i]]);
        }
        return ans;
    }
};

class Solution2
{
public:
    long long countBadPairs(std::vector<int>& nums)
    {
        int n = nums.size();
        long long ans = n * (n - 1LL) / 2LL;
        std::unordered_map<int, int> counter;
        for (int i = 0; i < n; ++i)
        {
            ans -= counter[nums[i] - i]++;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
