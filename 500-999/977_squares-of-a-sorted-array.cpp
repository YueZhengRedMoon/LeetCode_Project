#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<int> sortedSquares(std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> ans(n);

        int zeroIdx = std::lower_bound(nums.begin(), nums.end(), 0) - nums.begin();
        int i = zeroIdx - 1, j = zeroIdx, k = 0;

        while (k < n)
        {
            if (i >= 0 && j < n)
            {
                int i2 = nums[i] * nums[i], j2 = nums[j] * nums[j];
                if (i2 < j2)
                {
                    ans[k] = i2;
                    --i;
                }
                else
                {
                    ans[k] = j2;
                    ++j;
                }
            }
            else if (i >= 0)
            {
                ans[k] = nums[i] * nums[i];
                --i;
            }
            else
            {
                ans[k] = nums[j] * nums[j];
                ++j;
            }
            ++k;
        }

        return ans;
    }
};

class Solution2
{
public:
    std::vector<int> sortedSquares(std::vector<int>& nums)
    {
        int n = nums.size(), i = 0, j = n - 1, k = n - 1;
        std::vector<int> ans(n);
        while (k >= 0)
        {
            int i2 = nums[i] * nums[i], j2 = nums[j] * nums[j];
            if (i2 > j2)
            {
                ans[k--] = i2;
                ++i;
            }
            else
            {
                ans[k--] = j2;
                --j;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
