#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    bool hasPath(std::vector<std::vector<int>> &maze, std::vector<int> &start, std::vector<int> &destination)
    {
        const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        const int inf = 0x3f3f3f3f;
        int m = maze.size(), n = maze[0].size();
        int sx = start[0], sy = start[1];
        int dx = destination[0], dy = destination[1];

        std::queue<std::pair<int, int>> queue;
        std::vector<std::vector<int>> steps(m, std::vector<int>(n, inf));
        steps[sx][sy] = 0;
        queue.emplace(sx, sy);

        while (!queue.empty())
        {
            auto [x, y] = queue.front();
            queue.pop();

            if (x == dx && y == dy)
                return true;

            int step = steps[x][y] + 1;
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0], ny = y + dir[i][1];
                while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == 0)
                {
                    nx += dir[i][0];
                    ny += dir[i][1];
                }
                nx -= dir[i][0];
                ny -= dir[i][1];

                if ((nx != x || ny != y) && step < steps[nx][ny])
                {
                    steps[nx][ny] = step;
                    queue.emplace(nx, ny);
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