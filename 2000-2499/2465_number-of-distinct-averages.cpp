#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution
{
public:
    int distinctAverages(std::vector<int> &nums)
    {
        std::sort(nums.begin(), nums.end());
        std::unordered_set<int> set;
        int n = nums.size();
        for (int i = 0, j = n - 1; i < j; ++i, --j)
        {
            // 不需要除以2，平均值相同等价于两数之和相同
            set.insert(nums[i] + nums[j]);
        }
        return set.size();
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
