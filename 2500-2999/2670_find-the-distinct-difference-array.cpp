#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution
{
public:
    std::vector<int> distinctDifferenceArray(std::vector<int> &nums)
    {
        int numsSize = nums.size();
        std::unordered_map<int, int> suffix;
        std::unordered_set<int> prefix;
        std::vector<int> diff(numsSize);
        for (int i = 0; i < numsSize; ++i)
        {
            ++suffix[nums[i]];
        }

        for (int i = 0; i < numsSize; ++i)
        {
            if (--suffix[nums[i]] == 0)
            {
                suffix.erase(nums[i]);
            }
            prefix.insert(nums[i]);
            diff[i] = prefix.size() - suffix.size();
        }

        return diff;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
