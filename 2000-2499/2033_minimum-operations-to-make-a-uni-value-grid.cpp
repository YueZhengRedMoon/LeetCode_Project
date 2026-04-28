#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int minOperations(std::vector<std::vector<int>>& grid, int x)
    {
        // 一般地，对于整数 k，我们有 (grid[i][j]+kx)modx=grid[i][j]modx
        // 所以操作后，grid[i][j]modx 是不变的。每个数模 x 的结果必须都一样，才能变成同一个数。否则无解，输出 −1。

        int m = grid.size(), n = grid[0].size();
        int target = grid[0][0] % x;    // 每个数mod x都必须等于target，才可能有解
        std::vector<int> nums(m * n);
        for (int i = 0, k = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] % x != target)
                {
                    return -1;
                }
                nums[k++] = grid[i][j];
            }
        }

        // std::sort(nums.begin(), nums.end());
        std::nth_element(nums.begin(), nums.begin() + (m * n) / 2, nums.end()); // 用快速选择代替排序
        int median = nums[(m * n) / 2];

        int ans = 0;
        for (int v : nums)
        {
            ans += std::abs(v - median);
        }
        return ans / x;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}