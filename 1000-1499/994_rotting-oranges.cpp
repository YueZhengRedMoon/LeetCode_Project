#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int orangesRotting(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size(), fresh = 0;
        std::queue<std::pair<int, int>> q;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                    ++fresh;
                else if (grid[i][j] == 2)
                {
                    q.emplace(i, j);
                    grid[i][j] = -1;
                }
            }
        }

        const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        int ans = 0;
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0], ny = y + dir[i][1];
                if (0 <= nx && nx < m && 0 <= ny && ny < n && grid[nx][ny] == 1)
                {
                    --fresh;
                    grid[nx][ny] = grid[x][y] - 1;
                    ans = std::max(ans, -grid[nx][ny] - 1);
                    q.emplace(nx, ny);
                }
            }
        }

        return fresh == 0 ? ans : -1;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
