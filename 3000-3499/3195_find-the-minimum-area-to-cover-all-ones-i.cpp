#include <iostream>
#include <vector>

class Solution
{
public:
    int minimumArea(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        int top = m, bottom = -1, right = -1, left = n;
        // 寻找top
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j])
                {
                    top = std::min(top, i);
                    bottom = std::max(bottom, i);
                    left = std::min(left, j);
                    right = std::max(right, j);
                }
            }
        }
        return (bottom - top + 1) * (right - left + 1);
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
