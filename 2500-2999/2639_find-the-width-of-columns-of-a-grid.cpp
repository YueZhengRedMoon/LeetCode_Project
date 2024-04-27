#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<int> findColumnWidth(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        std::vector<int> ans(n, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ans[j] = std::max(ans[j], (int) std::to_string(grid[i][j]).size());
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
