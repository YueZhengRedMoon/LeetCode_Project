#include <iostream>
#include <vector>
#include <functional>

class Solution
{
public:
    bool containsCycle(std::vector<std::vector<char>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<bool>> visit(m, std::vector<bool>(n, false));
        const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::function<bool(int, int, int, int)> dfs = [&](int x, int y, int fx, int fy) -> bool {
            visit[x][y] = true;
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0], ny = y + dir[i][1];
                if (0 <= nx && nx < m && 0 <= ny && ny < n && !(nx == fx && ny == fy) && grid[x][y] == grid[nx][ny])
                {
                    if (visit[nx][ny] || dfs(nx, ny, x, y))
                    {
                        return true;
                    }
                }
            }
            return false;
        };

        for (int x = 0; x < m; ++x)
        {
            for (int y = 0; y < n; ++y)
            {
                if (!visit[x][y])
                {
                    if (dfs(x, y, -1, -1))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}