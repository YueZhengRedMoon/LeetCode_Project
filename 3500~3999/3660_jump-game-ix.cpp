#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> maxValue(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> preMax(n); // preMax[i]:nums[0,i]中的最大值
        preMax[0] = nums[0];
        for (int i = 1; i < n; ++i)
        {
            preMax[i] = std::max(preMax[i - 1], nums[i]);
        }

        std::vector<int> ans(n);
        int sufMin = INT_MAX;   // 从右向左遍历到nums[i]时，nums[i,n)中的最小值
        for (int i = n - 1; i >= 0; --i)
        {
            // preMax[i] <= sufMin:nums[0,i]中的元素无法跳到nums[i+1,n)中，ans[i]只能往左跳，故答案为preMax[i]
            // preMax[i] > sufMin:nums[i]可以先跳到nums[i+1,n)中的最小值，再跳到i+1，故答案为ans[i+1]
            ans[i] = preMax[i] <= sufMin ? preMax[i] : ans[i + 1];

            sufMin = std::min(sufMin, nums[i]);
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}