#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    bool containsNearbyDuplicate(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        std::unordered_map<int, std::vector<int>> indices;

        for (int i = 0; i < n; ++i)
        {
            std::vector<int> &numIndices = indices[nums[i]];
            int j = i - k;
            auto it = std::lower_bound(numIndices.begin(), numIndices.end(), j);
            if (it != numIndices.end())
            {
                return true;
            }
            numIndices.push_back(i);
        }

        return false;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {2, 2};
    int k = 3;
    bool ans = solution.containsNearbyDuplicate(nums, k);
    std::cout << std::boolalpha << ans << std::endl;
    return 0;
}
