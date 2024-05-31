#include <iostream>
#include <vector>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<int> findMissingAndRepeatedValues(std::vector<std::vector<int>>& grid)
    {
        int n = grid.size(), xorAll = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                xorAll ^= grid[i][j];
            }
        }
        xorAll ^= xorN(n * n);
        int shift = __builtin_ctz(xorAll);  // xorAll的尾随0个数

        // 分组异或
        std::vector<int> ans(2);
        for (int x = 1; x <= n * n; ++x)
        {
            ans[(x >> shift) & 1] ^= x;
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ans[(grid[i][j] >> shift) & 1] ^= grid[i][j];
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == ans[0])
                    return ans;
            }
        }

        return {ans[1], ans[0]};
    }

private:
    int xorN(int n)
    {
        switch (n % 4)
        {
            case 0: return n;
            case 1: return 1;
            case 2: return n + 1;
            default: return 0;
        }
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{1, 1}, {3, 2}};
    std::vector<int> ans = solution.findMissingAndRepeatedValues(grid);
    std::cout << ans[0] << ' ' << ans[1] << std::endl;
    return 0;
}
