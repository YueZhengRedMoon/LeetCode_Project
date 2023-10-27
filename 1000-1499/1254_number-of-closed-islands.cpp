#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    using Grid = std::vector<std::vector<int>>;

    int closedIsland(Grid &grid)
    {
        row = grid.size();
        col = grid[0].size();

        for (int i = 0; i < row; ++i)
        {
            if (grid[i][0] == 0)
                bfs(grid, i, 0);
            if (grid[i][col - 1] == 0)
                bfs(grid, i, col - 1);
        }
        for (int j = 1; j < col - 1; ++j)
        {
            if (grid[0][j] == 0)
                bfs(grid, 0, j);
            if (grid[row - 1][j] == 0)
                bfs(grid, row - 1, j);
        }

        int ans = 0;
        for (int i = 1; i < row - 1; ++i)
        {
            for (int j = 1; j < col - 1; ++j)
            {
                if (grid[i][j] == 0)
                {
                    ++ans;
                    bfs(grid, i, j);
                }
            }
        }

        return ans;
    }

private:
    int row;
    int col;
    const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void bfs(Grid &grid, int x, int y)
    {
        grid[x][y] = 1;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(x, y);
        while (!queue.empty())
        {
            x = queue.front().first;
            y = queue.front().second;
            queue.pop();

            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 0)
                {
                    queue.emplace(nx, ny);
                    grid[nx][ny] = 1;
                }
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}