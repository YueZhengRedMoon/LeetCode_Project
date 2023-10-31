#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int sumCounts(std::vector<int> &nums)
    {
        const int MOD = 1e9 + 7;
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            ans = (ans + 1) % MOD;
            std::unordered_set<int> set({nums[i]});
            for (int j = i + 1; j < n; ++j)
            {
                set.insert(nums[j]);
                int diff = set.size();
                ans = (ans + diff * diff % MOD) % MOD;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}