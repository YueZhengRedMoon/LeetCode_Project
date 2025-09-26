#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int triangleNumber(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int ans = 0, n = nums.size();
        for (int i = 0; i < n - 2; ++i)
        {
            for (int j = i + 1; j < n - 1; ++j)
            {
                auto begin = nums.begin() + j + 1;
                ans += std::lower_bound(begin, nums.end(), nums[i] + nums[j]) - begin;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int triangleNumber(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int ans = 0, n = nums.size();
        for (int k = 2; k < n; ++k)
        {
            int i = 0, j = k - 1, c = nums[k];
            while (i < j)
            {
                if (nums[i] + nums[j] > c)
                {
                    ans += j - i;
                    --j;
                }
                else
                {
                    ++i;
                }
            }
        }
        return ans;
    }
};

class Solution3
{
public:
    int triangleNumber(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int ans = 0, n = nums.size();
        for (int k = n - 1; k >= 2; --k)
        {
            int c = nums[k];    // 假设 1 <= a <= b <= c
            if (nums[0] + nums[1] > c)  // 最小的a+b都>c, nums[0, k]中任意3个元素都能组成有效三角形
            {
                ans += (k + 1) * k * (k - 1) / 6;
                break;
            }
            if (nums[k - 2] + nums[k - 1] <= c) // 最大的a+b都<=c, nums[0, k]中不可能组出有效三角形
            {
                continue;
            }

            int i = 0, j = k - 1;
            while (i < j)
            {
                if (nums[i] + nums[j] > c)
                {
                    ans += j - i;
                    --j;
                }
                else
                {
                    ++i;
                }
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
