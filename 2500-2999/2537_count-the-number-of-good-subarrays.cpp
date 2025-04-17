#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    long long countGood(std::vector<int>& nums, int k)
    {
        long long ans = 0;
        std::unordered_map<int, int> cnt;
        int pairs = 0, left = 0;
        for (int x : nums)
        {
            pairs += cnt[x]++;
            while (pairs >= k)
            {
                pairs -= --cnt[nums[left]];
                ++left;
            }
            ans += left;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {3,1,4,3,2,2,4};
    int k = 2;
    long long ans = solution.countGood(nums, k);
    std::cout << ans << std::endl;
    return 0;
}
