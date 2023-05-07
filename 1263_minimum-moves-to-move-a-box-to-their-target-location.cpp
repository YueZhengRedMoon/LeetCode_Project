#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include "debug.h"

struct Node
{
    int x, y;
    Node(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};

class Solution
{
public:
    int minPushBox(std::vector<std::vector<char>> &grid)
    {
        Node start, target, box;
        m = grid.size();
        n = grid[0].size();
        // 找到起始位置、目标位置和箱子的位置
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                switch (grid[i][j])
                {
                    case 'T':
                        target.x = i;
                        target.y = j;
                        break;
                    case 'S':
                        start.x = i;
                        start.y = j;
                        break;
                    case 'B':
                        box.x = i;
                        box.y = j;
                        break;
                }
            }
        }

        // 可达矩阵
        int reachable[MAX_M][MAX_N];
        std::memset(reachable, 0, sizeof(reachable));
        // 计算可达矩阵
        std::queue<Node> queue;
        queue.push(start);
        while (!queue.empty())
        {
            Node current = queue.front();
            queue.pop();

            for (int i = 0; i < 4; ++i)
            {
                int nextX = current.x + next[i][0];
                int nextY = current.y + next[i][1];
                if (isValid(nextX, nextY, grid) && (reachable[nextX][nextY] & (1 << i)) == 0)
                {
                    reachable[nextX][nextY] |= (1 << i);
                    queue.emplace(nextX, nextY);
                }
            }
        }
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                std::cout << reachable[i][j] << ' ';
            }
            std::cout << std::endl;
        }


        // 开始BFS
        int visited[MAX_M][MAX_N];
        std::memset(visited, 0, sizeof(visited));
        std::queue<std::pair<Node, int>> queue2;
        queue2.emplace(box, 0);
        visited[box.x][box.y] = 15;
        while (!queue2.empty())
        {
            auto currentStatus = queue2.front();
            Node &current = currentStatus.first;
            int step = currentStatus.second;
            queue2.pop();
            if (current.x == target.x && current.y == target.y)
            {
                return step;
            }

            std::cout << current.x << '\t' << current.y << '\t' << step << std::endl;

            for (int i = 0; i < 4; ++i)
            {
                // 推往的位置
                int nextX = current.x + next[i][0];
                int nextY = current.y + next[i][1];
                // 推的位置
                int j = (i % 2 == 0) ? i + 1 : i - 1;
                int fromX = current.x + next[j][0];
                int fromY = current.y + next[j][1];
                // 可以往下一个方向推，且可以从箱子所在位置以外其他的方向到达推的位置
                if (isValid(nextX, nextY, grid) && isValid(fromX, fromY, grid)
                    && (visited[nextX][nextY] & (1 << i)) == 0
                    // && !visited[nextX][nextY]
                    && (reachable[fromX][fromY] & ~(1 << j)))
                {
                    visited[nextX][nextY] |= (1 << i);
                    // visited[nextX][nextY] = 1;
                    queue2.push({{nextX, nextY}, step + 1});
                }
            }
        }

        return -1;
    }

private:
    const int MAX_M = 20;
    const int MAX_N = 20;
    const int next[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int m;
    int n;

    inline bool isValid(int x, int y, std::vector<std::vector<char>> &grid)
    {
        return x >= 0 && x < m && y > 0 && y < n && grid[x][y] != '#';
    }
};

class Solution2
{
public:
    int minPushBox(std::vector<std::vector<char>> &grid)
    {
        Node start, target, box;
        m = grid.size();
        n = grid[0].size();
        // 找到起始位置、目标位置和箱子的位置
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                switch (grid[i][j])
                {
                    case 'T':
                        target.x = i;
                        target.y = j;
                        break;
                    case 'S':
                        start.x = i;
                        start.y = j;
                        break;
                    case 'B':
                        box.x = i;
                        box.y = j;
                        break;
                }
            }
        }

        // 开始BFS
        int visited[MAX_M][MAX_N];
        std::memset(visited, 0, sizeof(visited));
        std::queue<std::pair<Node, int>> queue2;
        queue2.emplace(box, 0);
        visited[box.x][box.y] = 15;
        while (!queue2.empty())
        {
            auto currentStatus = queue2.front();
            Node &current = currentStatus.first;
            int step = currentStatus.second;
            queue2.pop();
            if (current.x == target.x && current.y == target.y)
            {
                return step;
            }

            std::cout << current.x << '\t' << current.y << '\t' << step << std::endl;

            for (int i = 0; i < 4; ++i)
            {
                // 推往的位置
                int nextX = current.x + next[i][0];
                int nextY = current.y + next[i][1];
                // 推的位置
                int j = (i % 2 == 0) ? i + 1 : i - 1;
                int fromX = current.x + next[j][0];
                int fromY = current.y + next[j][1];
                // 可以往下一个方向推，且可以从箱子所在位置以外其他的方向到达推的位置
                if (isValid(nextX, nextY, grid) && isValid(fromX, fromY, grid)
                    && (visited[nextX][nextY] & (1 << i)) == 0
                    && canReach({fromX, fromY}, {nextX, nextY}, current, grid))
                {
                    visited[nextX][nextY] |= (1 << i);
                    queue2.push({{nextX, nextY}, step + 1});
                }
            }
        }

        return -1;
    }

private:
    static const int MAX_M = 20;
    static const int MAX_N = 20;
    const int next[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool reachable[MAX_M][MAX_N];
    int m;
    int n;

    inline bool isValid(int x, int y, std::vector<std::vector<char>> &grid)
    {
        return x >= 0 && x < m && y > 0 && y < n && grid[x][y] != '#';
    }

    bool canReach(const Node &from, const Node &to, const Node &box, std::vector<std::vector<char>> &grid)
    {
        std::memset(reachable, 0, sizeof(reachable));
        std::queue<Node> queue;
        queue.emplace(from);
        reachable[from.x][from.y] = true;
        while (!queue.empty())
        {
            Node current = queue.front();
            queue.pop();

            if (current.x == to.x && current.y == to.y)
            {
                return true;
            }

            for (int i = 0; i < 4; ++i)
            {
                int nextX = current.x + next[i][0];
                int nextY = current.y + next[i][1];
                if (isValid(nextX, nextY, grid) && !reachable[nextX][nextY]
                    && !(nextX == box.x && nextY == box.y))
                {
                    reachable[nextX][nextY] = true;
                    queue.emplace(nextX, nextY);
                }
            }
        }
        return false;
    }
};


int main()
{
    Solution solution;
    std::vector<std::vector<char>> grid = {{'#','#','#','#','#','#'},
                                           {'#','T','#','#','#','#'},
                                           {'#','.','.','B','.','#'},
                                           {'#','.','#','#','.','#'},
                                           {'#','.','.','.','S','#'},
                                           {'#','#','#','#','#','#'}};
    int result = solution.minPushBox(grid);
    std::cout << result << std::endl;

    std::vector<std::vector<char>> grid2 = {{'#','.','.','#','#','#','#','#'},
                                            {'#','.','.','T','#','.','.','#'},
                                            {'#','.','.','.','#','B','.','#'},
                                            {'#','.','.','.','.','.','.','#'},
                                            {'#','.','.','.','#','.','S','#'},
                                            {'#','.','.','#','#','#','#','#'}};
    int result2 = solution.minPushBox(grid2);
    std::cout << result2 << std::endl;
    return 0;
}