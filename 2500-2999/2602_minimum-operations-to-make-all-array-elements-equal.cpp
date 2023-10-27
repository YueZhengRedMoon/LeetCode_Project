#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug.h"

class Solution
{
public:
    std::vector<long long> minOperations(std::vector<int> &nums, std::vector<int> &queries)
    {
        int numsSize = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<long long> prefix(numsSize, 0);
        prefix[0] = nums[0];
        for (int i = 1; i < numsSize; ++i)
        {
            prefix[i] = nums[i] + prefix[i - 1];
        }

        std::vector<long long> result(queries.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            long long query = queries[i];
            auto it = std::upper_bound(nums.begin(), nums.end(), queries[i]);
            int index = it - nums.begin();
            if (index < nums.size())
            {
                if (index > 0)
                {
                    result[i] = prefix[numsSize - 1] - prefix[index - 1] - (numsSize - index) * query
                                + index * query - prefix[index - 1];
                }
                else
                {
                    result[i] = prefix[numsSize - 1] - numsSize * query;
                }
            }
            else
            {
                result[i] = numsSize * query - prefix[numsSize - 1];
            }
        }

        return result;
    }
};

int main()
{
    std::vector<int> nums = {3, 1, 6, 8};
    std::vector<int> queries = {1, 5};
    Solution solution;
    std::vector<long long> result = solution.minOperations(nums, queries);
    debug::printVector(result);
    return 0;
}
