#include <iostream>
#include <vector>
#include <algorithm>
#include "../debug/debug.h"

class Solution
{
public:
    int deleteGreatestValue(std::vector<std::vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        for (std::vector<int> &row : grid)
        {
            std::sort(row.begin(), row.end(), std::greater<>());
        }
        for (int j = 0; j < n; ++j)
        {
            int maxVal = 0;
            for (int i = 0; i < m; ++i)
            {
                if (grid[i][j] > maxVal)
                    maxVal = grid[i][j];
            }
            ans += maxVal;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{1,2,4},{3,3,1}};
    int ans = solution.deleteGreatestValue(grid);
    println(ans);
    return 0;
}