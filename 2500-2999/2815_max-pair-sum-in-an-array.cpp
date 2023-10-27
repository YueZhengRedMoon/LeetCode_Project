#include <iostream>
#include <vector>
#include <limits>
#include "../debug.h"

class Solution
{
public:
    int maxSum(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> maxDigit(n);
        for (int i = 0; i < n; ++i)
        {
            maxDigit[i] = getMaxDigit(nums[i]);
        }
        int ans = -1;
        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (maxDigit[i] == maxDigit[j])
                {
                    ans = std::max(ans, nums[i] + nums[j]);
                }
            }
        }
        return ans;
    }

private:
    int getMaxDigit(int num)
    {
        int res = num % 10;
        num /= 10;
        while (num > 0)
        {
            res = std::max(res, num % 10);
            num /= 10;
        }
        return res;
    }
};

class Solution2
{
public:
    int maxSum(std::vector<int> &nums)
    {
        std::vector<int> maxNum(10, std::numeric_limits<int>::min());
        int ans = -1;
        for (int num : nums)
        {
            int maxDigit = getMaxDigit(num);
            ans = std::max(ans, num + maxNum[maxDigit]);
            if (num > maxNum[maxDigit])
                maxNum[maxDigit] = num;
        }
        return ans;
    }

private:
    int getMaxDigit(int num)
    {
        int res = num % 10;
        num /= 10;
        while (num > 0)
        {
            res = std::max(res, num % 10);
            num /= 10;
        }
        return res;
    }
};

int main()
{
    Solution solution;
    std::vector<int> nums = {84,91,18,59,27,9,81,33,17,58};
    int ans = solution.maxSum(nums);
    logObj(ans);
    return 0;
}
