#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

class Solution
{
public:
    using Grid = std::vector<std::vector<int>>;

    struct Range
    {
        int left{51};
        int right{-1};
        int top{51};
        int bottom{-1};
    };

    int numDistinctIslands(Grid &grid)
    {
        row = grid.size();
        col = grid[0].size();

        int k = 2;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (grid[i][j] == 1)
                {
                    Range islandRange;
                    dfs(grid, i, j, islandRange, k);
                    shapeSet.emplace(calcShape(grid, islandRange, k));
                    ++k;
                }
            }
        }

        return shapeSet.size();
    }

private:
    int row;
    int col;
    const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::unordered_set<std::string> shapeSet;

    void dfs(Grid &grid, int x, int y, Range &islandRange, int k)
    {
        grid[x][y] = k;
        if (y < islandRange.left)
            islandRange.left = y;
        if (y > islandRange.right)
            islandRange.right = y;
        if (x < islandRange.top)
            islandRange.top = x;
        if (x > islandRange.bottom)
            islandRange.bottom = x;

        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 1)
            {
                dfs(grid, nx, ny, islandRange, k);
            }
        }
    }

    std::string calcShape(Grid &grid, Range &islandRange, int k)
    {
        std::string shape;
        for (int i = islandRange.top; i <= islandRange.bottom; ++i)
        {
            long long line = 0;
            for (int j = islandRange.left; j <= islandRange.right; ++j)
            {
                if (grid[i][j] == k)
                {
                    ++line;
                }
                line <<= 1;
            }
            shape += std::to_string(line) + '\n';
        }
        return shape;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
