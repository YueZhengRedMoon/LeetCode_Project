#include <iostream>
#include <vector>

class Solution
{
public:
    long long countQuadruplets(std::vector<int>& nums)
    {
        int n = nums.size();
        // great[k][x]:nums[k]右边比x大的元素的数量
        std::vector<std::vector<int>> great(n, std::vector<int>(n + 1, 0));
        for (int k = n - 2; k >= 1; --k)
        {
            for (int x = 1; x < nums[k + 1]; ++x)
                great[k][x] = great[k + 1][x] + 1;
            for (int x = nums[k + 1]; x <= n; ++x)
                great[k][x] = great[k + 1][x];
        }

        long long ans = 0;
        std::vector<int> less(n + 1, 0);    // less[j][x]:nums[j]左边比x小的元素的数量
        for (int j = 1; j < n - 2; ++j)
        {
            for (int x = nums[j - 1] + 1; x <= n; ++x)
                ++less[x];

            for (int k = j + 1; k < n - 1; ++k)
            {
                if (nums[j] > nums[k])
                {
                    ans += (long long) less[nums[k]] * great[k][nums[j]];
                }
            }
        }

        return ans;
    }
};

class Solution2
{
public:
    long long countQuadruplets(std::vector<int>& nums)
    {
        int n = nums.size();
        // great[k][x]:nums[k]右边比x大的元素的数量
        std::vector<std::vector<int>> great(n, std::vector<int>(n + 1, 0));
        for (int k = n - 2; k >= 1; --k)
        {
            for (int x = 1; x <= nums[k + 1]; ++x)
                great[k][x] = great[k + 1][x] + 1;
            for (int x = nums[k + 1]; x <= n; ++x)
                great[k][x] = great[k + 1][x];
        }

        long long ans = 0;
        for (int j = 1; j < n - 2; ++j)
        {
            for (int k = j + 1; k < n - 1; ++k)
            {
                int x = nums[k];
                if (nums[j] > x)
                {
                    ans += (x - n + 1ll + j + great[j][x]) * great[k][nums[j]];
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
