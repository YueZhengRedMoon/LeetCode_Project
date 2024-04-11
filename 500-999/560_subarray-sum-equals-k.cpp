#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int subarraySum(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, std::vector<int>> sumMap;
        int n = nums.size();
        for (int i = 1; i < n; ++i)
        {
            nums[i] += nums[i - 1];
            sumMap[nums[i]].push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans += (nums[i] == k);
            auto it = sumMap.find(nums[i] + k);
            if (it != sumMap.end())
            {
                std::vector<int>& idx = it->second;
                ans += idx.end() - std::upper_bound(idx.begin(), idx.end(), i);
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
