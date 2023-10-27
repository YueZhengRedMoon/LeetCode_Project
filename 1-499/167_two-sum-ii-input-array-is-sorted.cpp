#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug.h"

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target)
    {
        std::vector<int> ans(2);
        for (int i = 0; i < numbers.size(); ++i)
        {
            if (i > 0 && numbers[i] == numbers[i - 1])
                continue;
            auto it = std::lower_bound(numbers.begin() + i + 1, numbers.end(), target - numbers[i]);
            if (it != numbers.end() && numbers[i] + *it == target)
            {
                ans[0] = i + 1;
                ans[1] = it - numbers.begin() + 1;
                break;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target)
    {
        int left = 0, right = numbers.size() - 1;
        while (numbers[left] + numbers[right] != target)
        {
            if (numbers[left] + numbers[right] > target)
            {
                do
                {
                    --right;
                } while (numbers[right] == numbers[right + 1]);
            }
            else
            {
                do
                {
                    ++left;
                } while (numbers[left] == numbers[left - 1]);
            }
        }
        return {left + 1, right + 1};
    }
};

int main()
{
    Solution2 solution;
    std::vector<int> numbers = {2, 7, 11, 15};
    std::vector<int> ans = solution.twoSum(numbers, 9);
    debug::printVector(ans);
    return 0;
}