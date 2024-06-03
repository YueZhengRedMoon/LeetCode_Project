#include <iostream>
#include <vector>
#include <random>
#include "../debug/debug.h"

class Solution
{
public:
    int minimumDifference(std::vector<int>& nums, int k)
    {
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); ++i)
        {
            ans = std::min(ans, std::abs(nums[i] - k));
            for (int j = i - 1; j >= 0; --j)
            {
                if ((nums[j] & nums[i]) == nums[j])
                    break;
                nums[j] &= nums[i];
                ans = std::min(ans, std::abs(nums[j] - k));
            }
        }
        return ans;
    }
};

// --- 扩展 ---

// OR
class SolutionOR
{
public:
    int minimumDifference(std::vector<int>& nums, int k)
    {
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); ++i)
        {
            ans = std::min(ans, std::abs(nums[i] - k));
            for (int j = i - 1; j >= 0; --j)
            {
                if ((nums[j] | nums[i]) == nums[j])
                    break;
                nums[j] |= nums[i];
                ans = std::min(ans, std::abs(nums[j] - k));
            }
        }
        return ans;
    }

    int minimumDifferenceOn2(std::vector<int>& nums, int k)
    {
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); ++i)
        {
            ans = std::min(ans, std::abs(nums[i] - k));
            for (int j = i - 1; j >= 0; --j)
            {
                nums[j] |= nums[i];
                ans = std::min(ans, std::abs(nums[j] - k));
            }
        }
        return ans;
    }
};

int main()
{
    int minNum = 1, maxNum = 1000000000;
    int minN = 1000, maxN = 10000;
    int minK = 1, maxK = 10000;
    int ans1, ans2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disN(minN, maxN), disK(minK, maxK), disNum(minNum, maxNum);

    int n = disN(gen), k = disK(gen);
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        nums[i] = disNum(gen);
    }
    std::cout << "n = " << n << ", k = " << k << std::endl;

    SolutionOR solutionOr;
    std::vector<int> nums1 = nums, nums2 = nums;
    ans1 = solutionOr.minimumDifference(nums1, k);
    ans2 = solutionOr.minimumDifferenceOn2(nums2, k);
    std::cout << "ans1 = " << ans1 << ", ans2 = " << ans2 << std::endl;
    return 0;
}
