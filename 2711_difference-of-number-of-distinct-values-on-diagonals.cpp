#include <iostream>
#include <vector>
#include <cstring>
#include "debug.h"

class Solution
{
public:
    using Matrix = std::vector<std::vector<int>>;
    Matrix differenceOfDistinctValues(Matrix &grid)
    {
        int m = grid.size(), n = grid[0].size();
        bool set[51];
        Matrix ans(m, std::vector<int>(n, 0));
        for (int col = 0; col < n; ++col)
        {
            std::memset(set, 0, sizeof(set));
            for (int i = 0; i < m - 1 && col + i < n - 1; ++i)
            {
                int j = col + i;
                ans[i + 1][j + 1] = ans[i][j] + !set[grid[i][j]];
                set[grid[i][j]] = true;
            }
        }
        for (int row = 0; row < m; ++row)
        {
            std::memset(set, 0, sizeof(set));
            for (int j = 0; j < n - 1 && row + j < m - 1; ++j)
            {
                int i = row + j;
                ans[i + 1][j + 1] = ans[i][j] + !set[grid[i][j]];
                set[grid[i][j]] = true;
            }
        }
        for (int j = 1; j < n; ++j)
        {
            int bottomRight = 0;
            std::memset(set, 0, sizeof(set));
            for (int i = 0; i < m - 1 && i < j; ++i)
            {
                int row = m - 1 - i;
                int col = j - i;
                bottomRight += !set[grid[row][col]];
                set[grid[row][col]] = true;
                ans[row - 1][col - 1] = std::abs(ans[row - 1][col - 1] - bottomRight);
            }
        }
        for (int i = 1; i < m - 1; ++i)
        {
            int bottomRight = 0;
            std::memset(set, 0, sizeof(set));
            for (int j = 0; j < n - 1 && j < i; ++j)
            {
                int row = i - j;
                int col = n - 1 - j;
                bottomRight += !set[grid[row][col]];
                set[grid[row][col]] = true;
                ans[row - 1][col - 1] = std::abs(ans[row - 1][col - 1] - bottomRight);
            }
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{27,10,37},
                                          {43,27,48},
                                          {22,50,23},
                                          {37,49,45},
                                          {14,18,39},
                                          {50,7,31},
                                          {37,3,32},
                                          {25,21,22},
                                          {26,49,14}};
    std::vector<std::vector<int>> ans = solution.differenceOfDistinctValues(grid);
    debug::printVector2D(ans);
    return 0;
}