#include <iostream>
#include <vector>

class Solution
{
public:
    int maxKilledEnemies(std::vector<std::vector<char>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<int>> left(m, std::vector<int>(n, 0));
        std::vector<std::vector<int>> right(left), up(left), down(left);

        for (int i = 0; i < m; ++i)
        {
            left[i][0] = 0;
            for (int j = 1; j < n; ++j)
            {
                if (grid[i][j] == 'W') continue;
                left[i][j] = left[i][j - 1];
                if (grid[i][j - 1] == 'E')
                    ++left[i][j];
            }

            right[i][n - 1] = 0;
            for (int j = n - 2; j >= 0; --j)
            {
                if (grid[i][j] == 'W') continue;
                right[i][j] = right[i][j + 1];
                if (grid[i][j + 1] == 'E')
                    ++right[i][j];
            }
        }

        for (int j = 0; j < n; ++j)
        {
            up[0][j] = 0;
            for (int i = 1; i < m; ++i)
            {
                if (grid[i][j] == 'W') continue;
                up[i][j] = up[i - 1][j];
                if (grid[i - 1][j] == 'E')
                    ++up[i][j];
            }

            down[m - 1][j] = 0;
            for (int i = m - 2; i >= 0; --i)
            {
                if (grid[i][j] == 'W') continue;
                down[i][j] = down[i + 1][j];
                if (grid[i + 1][j] == 'E')
                    ++down[i][j];
            }
        }

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] != '0') continue;
                ans = std::max(ans, left[i][j] + right[i][j] + up[i][j] + down[i][j]);
            }
        }

        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}