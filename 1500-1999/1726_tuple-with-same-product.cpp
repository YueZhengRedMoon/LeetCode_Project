#include <iostream>
#include <vector>
#include <unordered_map>
#include "../debug.h"

class Solution
{
public:
    int tupleSameProduct(std::vector<int> &nums)
    {
        int ans = 0, n = nums.size();
        std::unordered_map<int, int> counter;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                    ++counter[nums[i] * nums[j]];
            }
        }
        for (auto [product, count] : counter)
        {
            std::cout << "product = " << product << ", count = " << count << std::endl;
            ans += count * (count - 2);
        }
        return ans;
    }
};

class Solution2
{
public:
    int tupleSameProduct(std::vector<int> &nums)
    {
        int ans = 0, n = nums.size();
        std::unordered_map<int, int> counter;
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                ++counter[nums[i] * nums[j]];
            }
        }
        for (auto [_, count] : counter)
        {
            ans += count * (count - 1) * 4;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {2, 3, 4, 6};
    int ans = solution.tupleSameProduct(nums);
    logObj(ans);
    return 0;
}
