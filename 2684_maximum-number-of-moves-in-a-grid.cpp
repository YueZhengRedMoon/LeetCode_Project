#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

class Solution
{
public:
    using tuple3 = std::tuple<int, int, int>;

    int maxMoves(std::vector<std::vector<int>> &grid)
    {
        row = grid.size();
        col = grid[0].size();
        maxStep = 0;
        arrive = std::vector<std::vector<int>>(row, std::vector<int>(col, 0));

        for (int i = 0; i < row; ++i)
        {
            bfs(grid, i, 0);
        }

        return maxStep;
    }

private:
    int row;
    int col;
    int dir[3][2] = {{-1, 1}, {0, 1}, {1, 1}};
    int maxStep;
    std::vector<std::vector<int>> arrive;

    void bfs(std::vector<std::vector<int>> &grid, int startX, int startY)
    {
        std::queue<tuple3> queue;
        queue.push(tuple3(startX, startY, 0));
        while (!queue.empty())
        {
            auto [x, y, step] = queue.front();
            queue.pop();
            if (step > maxStep)
            {
                maxStep = step;
            }
            ++step;

            for (int i = 0; i < 3; ++i)
            {
                int nextX = x + dir[i][0];
                int nextY = y + dir[i][1];
                if (isValid(grid, x, y, nextX, nextY, step))
                {
                    arrive[nextX][nextY] = step;
                    queue.push(tuple3(nextX, nextY, step));
                }
            }
        }
    }

    inline bool isValid(std::vector<std::vector<int>> &grid, int fromX, int fromY, int toX, int toY, int step)
    {
        return toX >= 0 && toX < row && toY < col && grid[toX][toY] > grid[fromX][fromY] && step > arrive[toX][toY];
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{3, 2 ,4}, {2, 1, 9}, {1, 1, 7}};
    int result = solution.maxMoves(grid);
    std::cout << result << std::endl;
    return 0;
}
