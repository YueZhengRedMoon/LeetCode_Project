#include <iostream>
#include <vector>
#include <unordered_set>

class Solution
{
public:
    int maximumUniqueSubarray(std::vector<int>& nums)
    {
        int n = nums.size(), ans = 0, score = 0;
        std::unordered_set<int> subArr;
        for (int i = 0, j = 0; j < n; ++j)
        {
            while (!subArr.empty() && subArr.find(nums[j]) != subArr.end())
            {
                score -= nums[i];
                subArr.erase(nums[i]);
                ++i;    // 对i+1的总执行次数不会超过n次，所以总循环次数为O(n)
            }

            subArr.insert(nums[j]);
            score += nums[j];

            if (score > ans)
                ans = score;
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
