#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxScore(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = INT_MIN;
        // f[i][j]:以grid[i][j]为右下角，grid[0][0]为左上角的二维数组中的元素的最小值
        std::vector<int> f(n, INT_MAX);

        for (int i = 0; i < m; ++i)
        {
            ans = std::max(ans, grid[i][0] - f[0]);
            f[0] = std::min(f[0], grid[i][0]);
            std::cout << f[0] << '\t';

            for (int j = 1; j < n; ++j)
            {
                ans = std::max(ans, grid[i][j] - std::min(f[j], f[j - 1]));
                f[j] = std::min({f[j - 1], f[j], grid[i][j]});
                std::cout << f[j] << '\t';
            }
            std::cout << std::endl;
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{4, 3},
                                          {2, 3}};
    int ans = solution.maxScore(grid);
    std::cout << ans << std::endl;
    return 0;
}
