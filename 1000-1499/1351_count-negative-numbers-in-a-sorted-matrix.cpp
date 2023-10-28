#include <iostream>
#include <vector>
#include "../debug/debug.h"

class Solution
{
public:
    int countNegatives(std::vector<std::vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        for (int i = 0; i < m; ++i)
        {
            int left = 0, right = n;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (grid[i][mid] < 0)
                {
                    right = mid;
                }
                else
                {
                    left = mid + 1;
                }
            }
            ans += n - left;
        }
        return ans;
    }
};

class Solution2
{
public:
    int countNegatives(std::vector<std::vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        int i, j;
        for (i = 0, j = n - 1; i < m && j >= 0; ++i)
        {
            while (j >= 0 && grid[i][j] < 0)
                --j;

            ans += n - j - 1;
        }
        ans += (m - i) * n;
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{4,3,2,-1},{3,2,1,-1},{1,1,-1,-2},{-1,-1,-2,-3}};
    int ans = solution.countNegatives(grid);
    logObj(ans);
    return 0;
}
