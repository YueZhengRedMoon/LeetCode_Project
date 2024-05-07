#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int cherryPickup(std::vector<std::vector<int>>& grid)
    {
        int rows = grid.size(), cols = grid[0].size();
        // f[i][j1][j2]:机器人1到达grid[i][j1]，机器人2到达grid[i][j2]时能获得的最大樱桃数
        std::vector<std::vector<std::vector<int>>> f(2, std::vector<std::vector<int>>(cols + 2, std::vector<int>(cols + 2, INT_MIN)));
        f[0][1][cols] = grid[0][0] + grid[0][cols - 1];

        for (int i = 1; i < rows; ++i)
        {
            int cur = i % 2, last = (i - 1) % 2;
            for (int j1 = 1; j1 <= cols; ++j1)
            {
                for (int j2 = 1; j2 <= cols; ++j2)
                {
                    f[cur][j1][j2] = std::max({
                                            f[last][j1 - 1][j2 - 1], f[last][j1 - 1][j2], f[last][j1 - 1][j2 + 1],
                                            f[last][j1][j2 - 1], f[last][j1][j2], f[last][j1][j2 + 1],
                                            f[last][j1 + 1][j2 - 1], f[last][j1 + 1][j2], f[last][j1 + 1][j2 + 1]
                    });
                    f[cur][j1][j2] += (j1 == j2 ? grid[i][j1 - 1] : grid[i][j1 - 1] + grid[i][j2 - 1]);
                }
            }
        }

        rows = (rows - 1) % 2;
        int ans = 0;
        for (int j1 = 1; j1 <= cols; ++j1)
        {
            for (int j2 = 1; j2 <= cols; ++j2)
            {
                if (f[rows][j1][j2] > ans)
                    ans = f[rows][j1][j2];
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
