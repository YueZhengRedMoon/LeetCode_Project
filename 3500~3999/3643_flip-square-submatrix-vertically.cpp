#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> reverseSubmatrix(std::vector<std::vector<int>>& grid, int x, int y, int k)
    {
        for (int r1 = x, r2 = x + k - 1; r1 < r2; ++r1, --r2)
        {
            for (int j = y; j < y + k; ++j)
            {
                std::swap(grid[r1][j], grid[r2][j]);
            }
        }
        return grid;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}