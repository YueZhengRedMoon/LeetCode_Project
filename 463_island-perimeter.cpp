#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    using Grid = std::vector<std::vector<int>>;

    int islandPerimeter(Grid &grid)
    {
        int row = grid.size();
        int col = grid[0].size();
        Grid visited(row, std::vector<int>(col, 0));

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (grid[i][j] == 1)
                {
                    return bfs(grid, visited, i, j);
                }
            }
        }

        return 0;
    }

private:
    int bfs(Grid &grid, Grid &visited, int x, int y)
    {
        int next[4][2] = {{1, 0} , {-1, 0}, {0, 1}, {0, -1}};
        int perimeter = 0;
        std::queue<std::pair<int, int>> queue;
        queue.push({x, y});
        while (!queue.empty())
        {
            std::pair<int, int> current = queue.front();
            queue.pop();
            visited[current.first][current.second] = true;

            for (int i = 0; i < 4; ++i)
            {
                int nextX = current.first + next[i][0];
                int nextY = current.second + next[i][1];

                if (isValid(grid, nextX, nextY))
                {
                    if (!visited[nextX][nextY])
                    {
                        queue.push({nextX, nextY});
                    }
                }
                else
                {
                    ++perimeter;
                }
            }
        }

        return perimeter;
    }

    inline bool isValid(Grid &grid, int x, int y)
    {
        int row = grid.size();
        int col = grid[0].size();

        return x >= 0 && x < row && y >= 0 && y < col && grid[x][y];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}