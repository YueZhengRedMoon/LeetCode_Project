#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "../debug.h"

class Solution
{
public:
    std::vector<long long> distance(std::vector<int> &nums)
    {
        int numsSize = nums.size();
        std::unordered_map<int, std::vector<int>> group;            // 每个数及其出现的索引
        std::unordered_map<int, std::vector<long long>> prefix;     // 每个数及其出现索引的前缀和
        for (int i = 0; i < numsSize; ++i)
        {
            group[nums[i]].push_back(i);
            if (prefix.find(nums[i]) == prefix.end())
            {
                prefix.insert({nums[i], {i}});
            }
            else
            {
                auto &prefixVec = prefix[nums[i]];
                prefixVec.push_back(prefixVec.back() + i);
            }
        }

        std::vector<long long> result(numsSize);
        for (int i = 0; i < numsSize; ++i)
        {
            auto &indices = group[nums[i]];
            auto &prefixVec = prefix[nums[i]];
            auto it = std::lower_bound(indices.begin(), indices.end(), i);
            long long index = it - indices.begin();
            int n = prefixVec.size();
            if (index < n)
            {
                if (index > 0)
                {
                    result[i] = prefixVec[n - 1] - prefixVec[index - 1] - (n - index) * i + i * index - prefixVec[index - 1];
                }
                else
                {
                    result[i] = prefixVec[n - 1] - i * n;
                }
            }
            else
            {
                result[i] = i * n - prefixVec[n - 1];
            }
        }

        return result;
    }
};

class Solution3
{
public:
    std::vector<long long> distance(std::vector<int> &nums)
    {
        int numsSize = nums.size();
        std::unordered_map<int, std::vector<int>> group;
        for (int i = 0; i < numsSize; ++i)
        {
            group[nums[i]].push_back(i);
        }

        std::vector<long long> result(numsSize);
        for (auto it = group.begin(); it != group.end(); ++it)
        {
            auto &indices = it->second;
            int n = indices.size();
            long long sum = 0;
            for (int i = 1; i < n; ++i)
            {
                sum += indices[i] - indices[0];
            }
            result[indices[0]] = sum;
            for (int i = 1; i < n; ++i)
            {
                sum += (2 * i - n) * (indices[i] - indices[i - 1]);
                result[indices[i]] = sum;
            }
        }

        return result;
    }
};

int main()
{
    std::vector<int> nums = {1, 3, 1, 1, 2};
    Solution solution;
    std::vector<long long> result = solution.distance(nums);
    debug::printVector(result);
    return 0;
}