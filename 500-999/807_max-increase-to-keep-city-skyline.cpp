#include <iostream>
#include <vector>

class Solution
{
public:
    int maxIncreaseKeepingSkyline(std::vector<std::vector<int>>& grid)
    {
        int n = grid.size();
        // 0:南北 1:东西
        std::vector<std::vector<int>> skyline(2, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int height = grid[i][j];
                if (height > skyline[0][j])
                    skyline[0][j] = height;
                if (height > skyline[1][i])
                    skyline[1][i] = height;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ans += std::min(skyline[0][j], skyline[1][i]) - grid[i][j];
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
