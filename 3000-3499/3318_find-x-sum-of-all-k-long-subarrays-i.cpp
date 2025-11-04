#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

class Solution
{
public:
    std::vector<int> findXSum(std::vector<int>& nums, int k, int x)
    {
        int n = nums.size();
        std::vector<int> ans;
        ans.reserve(n - k + 1);
        std::unordered_map<int, int> counter;

        for (int i = 0; i < k - 1; ++i)
        {
            ++counter[nums[i]];
        }

        int i = 0, j = k - 1;
        while (j < n)
        {
            ++counter[nums[j]];

            std::vector<std::pair<int, int>> pairs(counter.begin(), counter.end());
            std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) -> bool {
                if (a.second == b.second)
                {
                    return a.first > b.first;
                }
                return a.second > b.second;
            });

            std::unordered_set<int> xSet;
            for (int t = 0; t < std::min<int>(x, pairs.size()); ++t)
            {
                xSet.insert(pairs[t].first);
            }

            int xSum = 0;
            for (int t = i; t <= j; ++t)
            {
                if (xSet.find(nums[t]) != xSet.end())
                {
                    xSum += nums[t];
                }
            }
            ans.push_back(xSum);

            --counter[nums[i++]];
            ++j;
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}