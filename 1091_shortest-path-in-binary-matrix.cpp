#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

class Solution
{
public:
    using Tuple3 = std::tuple<int, int, int>;

    int shortestPathBinaryMatrix(std::vector<std::vector<int>> &grid)
    {
        if (grid[0][0] == 1)
        {
            return -1;
        }
        const int n = grid.size();
        const int inf = std::numeric_limits<int>::max();
        std::vector<std::vector<int>> visited(n, std::vector<int>(n, inf));
        std::queue<Tuple3> queue;
        visited[0][0] = 1;
        queue.push(std::make_tuple(0, 0, 1));
        while (!queue.empty())
        {
            auto [x, y, step] = queue.front();
            queue.pop();
            if (x == n - 1 && y == n - 1)
            {
                return step;
            }
            ++step;
            for (int i = 0; i < 8; ++i)
            {
                int nextX = x + dir[i][0];
                int nextY = y + dir[i][1];
                if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < n
                    && grid[nextX][nextY] == 0 && visited[nextX][nextY] > step)
                {
                    visited[nextX][nextY] = step;
                    queue.emplace(nextX, nextY, step);
                }
            }
        }
        return -1;
    }

private:
    const int dir[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1},
                           {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}