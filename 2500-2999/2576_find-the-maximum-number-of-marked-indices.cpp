#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxNumOfMarkedIndices(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        int n = nums.size(), left = 0, right = (n / 2) + 1, ans = 0;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (check(nums, mid))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        return ans * 2;
    }

private:
    // 检查从小到大排序的数组nums，是否可以从中选出k(0 <= k <= n/2)个数对
    // 对其中的每个数对nums[i],nums[j]满足nums[i]*2<=nums[j]
    // 如果可以找到这样的k个数对，则nums中的最小的k个数一定可以和最大k个数匹配
    bool check(const std::vector<int>& nums, int k)
    {
        int n = nums.size();
        for (int i = 0; i < k; ++i)
        {
            if (nums[i] * 2 > nums[n - k + i])
                return false;
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
