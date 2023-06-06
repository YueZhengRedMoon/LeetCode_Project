#include <iostream>
#include <vector>
#include <queue>
#include <functional>

class Solution
{
public:
    int shortestDistance(std::vector<std::vector<int>> &maze,
                         std::vector<int> &start, std::vector<int> &destination)
    {
        const int inf = 0x3f3f3f3f;
        const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int m = maze.size(), n = maze[0].size();
        int sx = start[0], sy = start[1], dx = destination[0], dy = destination[1];
        std::vector<std::vector<int>> dis(m, std::vector<int>(n, inf));
        dis[sx][sy] = 0;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(sx, sy);
        while (!queue.empty())
        {
            auto [x, y] = queue.front();
            queue.pop();
            if (x == dx && y == dy)
            {
                continue;
            }
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0], ny = y + dir[i][1], step = 1;
                while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] != 1)
                {
                    nx += dir[i][0];
                    ny += dir[i][1];
                    ++step;
                }
                if (step > 1)
                {
                    nx -= dir[i][0];
                    ny -= dir[i][1];
                    --step;
                    if (dis[x][y] + step < dis[nx][ny])
                    {
                        dis[nx][ny] = dis[x][y] + step;
                        queue.emplace(nx, ny);
                    }
                }
            }
        }
        return dis[dx][dy] == inf ? -1 : dis[dx][dy];
    }
};

class Solution2
{
public:
    int shortestDistance(std::vector<std::vector<int>> &maze,
                         std::vector<int> &start, std::vector<int> &destination)
    {
        m = maze.size();
        n = maze[0].size();
        int sx = start[0], sy = start[1];
        dx = destination[0];
        dy = destination[1];
        dis.resize(m, std::vector<int>(n, inf));
        dis[sx][sy] = 0;

        dfs(maze, sx, sy);

        return dis[dx][dy] == inf ? -1 : dis[dx][dy];
    }

private:
    int m, n;
    int dx, dy;
    const int inf{0x3f3f3f3f};
    const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::vector<int>> dis;

    void dfs(std::vector<std::vector<int>> &maze, int x, int y)
    {
        std::cout << "dis[" << x << "][" << y << "] = " << dis[x][y] << std::endl;
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dir[i][0], ny = y + dir[i][1], step = 1;
            while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] != 1)
            {
                nx += dir[i][0];
                ny += dir[i][1];
                ++step;
            }
            if (step > 1)
            {
                nx -= dir[i][0];
                ny -= dir[i][1];
                --step;
                if (dis[x][y] + step < dis[nx][ny])
                {
                    dis[nx][ny] = dis[x][y] + step;
                    if (nx != dx || ny != dy)
                    {
                        dfs(maze, nx, ny);
                    }
                }
            }
        }
    }
};

class Solution3
{
public:
    struct Status
    {
        int x;
        int y;
        int cost;
        Status(int x_ = 0, int y_ = 0, int cost_ = 0)
        : x(x_), y(y_), cost(cost_) {}
    };

    int shortestDistance(std::vector<std::vector<int>> &maze,
                         std::vector<int> &start, std::vector<int> &destination)
    {
        const int inf = 0x3f3f3f3f;
        const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int m = maze.size(), n = maze[0].size();
        int sx = start[0], sy = start[1], dx = destination[0], dy = destination[1];
        std::vector<std::vector<int>> dis(m, std::vector<int>(n, inf));
        dis[sx][sy] = 0;
        std::priority_queue<Status,
                            std::vector<Status>,
                            std::function<bool(const Status &lhs, const Status &rhs)>>
                            queue([](const Status &lhs, const Status &rhs)->bool {
                                return lhs.cost > rhs.cost;
                            });
        queue.emplace(sx, sy, 0);
        while (!queue.empty())
        {
            auto [x, y, cost] = queue.top();
            queue.pop();
            if (cost > dis[x][y] || (x == dx && y == dy))
            {
                continue;
            }
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0], ny = y + dir[i][1], step = 1;
                while (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] != 1)
                {
                    nx += dir[i][0];
                    ny += dir[i][1];
                    ++step;
                }
                if (step > 1)
                {
                    nx -= dir[i][0];
                    ny -= dir[i][1];
                    --step;
                    int newCost = dis[x][y] + step;
                    if (newCost < dis[nx][ny])
                    {
                        dis[nx][ny] = newCost;
                        queue.emplace(nx, ny, newCost);
                    }
                }
            }
        }
        return dis[dx][dy] == inf ? -1 : dis[dx][dy];
    }
};

int main()
{
    Solution2 solution;
    std::vector<std::vector<int>> maze = {{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}};
    std::vector<int> start = {0, 4};
    std::vector<int> destination = {4, 4};
    int ans = solution.shortestDistance(maze, start, destination);
    std::cout << ans << std::endl;
    return 0;
}
