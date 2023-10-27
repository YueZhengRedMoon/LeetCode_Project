#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    struct Status
    {
        int x;
        int y;
        int cost;
        std::string path;

        Status(int x_, int y_, int cost_, const std::string &path_)
        : x(x_), y(y_), cost(cost_), path(path_) {}

        bool operator > (const Status &rhs) const
        {
            return cost > rhs.cost;
        }
    };

    std::string findShortestWay(std::vector<std::vector<int>> &maze, std::vector<int> &ball, std::vector<int> &hole)
    {
        const int next[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        const char dir[4] = {'u', 'd', 'l', 'r'};
        const int inf{0x3f3f3f3f};
        int m = maze.size(), n = maze[0].size();
        int bx = ball[0], by = ball[1];
        int hx = hole[0], hy = hole[1];
        std::vector<std::vector<int>> dis(m, std::vector<int>(n, inf));
        std::vector<std::vector<std::string>> path(m, std::vector<std::string>(n, "impossible"));
        dis[bx][by] = 0;
        path[bx][by] = "";
        std::priority_queue<Status, std::vector<Status>, std::greater<>> queue;
        queue.emplace(bx, by, 0, "");
        auto isValid = [&](int x, int y) -> bool {
            return x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0;
        };

        while (!queue.empty())
        {
            auto [x, y, cost, curPath] = queue.top();
            queue.pop();
            if ((cost > dis[x][y]) || (cost == dis[x][y] && curPath > path[x][y]))
                continue;

            for (int i = 0; i < 4; ++i)
            {
                int nx = x, ny = y, step = 0;
                bool meetHole = false;
                while (isValid(nx + next[i][0], ny + next[i][1]))
                {
                    nx += next[i][0];
                    ny += next[i][1];
                    ++step;
                    // 球经过了洞穴
                    if (nx == hx && ny == hy)
                    {
                        meetHole = true;
                        break;
                    }
                }
                // 一步都没有走，直接搜索下一个方向
                if (step == 0)
                    continue;
                std::string newPath = curPath + dir[i];
                int newCost = cost + step;
                // 掉进了洞穴，更新答案
                if (meetHole)
                {
                    if (newCost < dis[hx][hy])
                    {
                        dis[hx][hy] = newCost;
                        path[hx][hy] = newPath;
                    }
                    else if (newCost == dis[hx][hy] && newPath < path[hx][hy])
                    {
                        path[hx][hy] = newPath;
                    }
                    continue;
                }
                // 球停了下来
                if (newCost < dis[nx][ny] || (newCost == dis[nx][ny] && newPath < path[nx][ny]))
                {
                    dis[nx][ny] = newCost;
                    path[nx][ny] = newPath;
                    queue.emplace(nx, ny, newCost, newPath);
                }
            }
        }

        return path[hx][hy];
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> maze = {{0,0,0,0,0},
                                          {1,1,0,0,1},
                                          {0,0,0,0,0},
                                          {0,1,0,0,1},
                                          {0,1,0,0,0}};
    std::vector<int> ball = {4, 3};
    std::vector<int> hole = {0, 1};
    std::string ans = solution.findShortestWay(maze, ball, hole);
    std::cout << ans << std::endl;
    return 0;
}
