#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> smallerNumbersThanCurrent(std::vector<int> &nums)
    {
        std::vector<int> sortNums;
        sortNums.reserve(nums.size());
        std::copy(nums.begin(), nums.end(), std::back_inserter(sortNums));
        std::sort(sortNums.begin(), sortNums.end());

        std::vector<int> result(nums.size(), 0);
        for (int i = 0; i < nums.size(); ++i)
        {
            auto it = std::lower_bound(sortNums.begin(), sortNums.end(), nums[i]);
            if (it != sortNums.end())
            {
                result[i] = it - sortNums.begin();
            }
        }

        return result;
    }
};

class Solution2
{
public:
    std::vector<int> smallerNumbersThanCurrent(std::vector<int> &nums)
    {
        std::vector<int> vec = nums;
        std::sort(vec.begin(), vec.end());
        int hash[101];
        for (int i = vec.size() - 1; i >= 0; --i)
        {
            hash[vec[i]] = i;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            vec[i] = hash[nums[i]];
        }

        return vec;
    }
};

int main()
{
    return 0;
}