#include <iostream>
#include <vector>

class Solution
{
public:
    bool satisfiesConditions(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i + 1 < m && grid[i][j] != grid[i + 1][j])
                    return false;
                if (j + 1 < n && grid[i][j] == grid[i][j + 1])
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
