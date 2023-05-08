#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <limits>
#include "debug.h"

struct Node
{
    int x, y;
    Node(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    bool operator==(const Node &other) const
    {
        return x == other.x && y == other.y;
    }
};

/** 错误 */
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
        Node start, initBox;
        int m = grid.size();
        int n = grid[0].size();
        // 找到起始位置、目标位置和箱子的位置
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 'S')
                {
                    start.x = i;
                    start.y = j;
                }
                else if (grid[i][j] == 'B')
                {
                    initBox.x = i;
                    initBox.y = j;
                }
            }
        }

        int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::vector<std::vector<int>> dp(m * n, std::vector<int>(m * n, std::numeric_limits<int>::max()));
        auto isValid = [&](const Node &node) -> bool
        {
            return node.x >= 0 && node.x < m && node.y >= 0 && node.y < n && grid[node.x][node.y] != '#';
        };
        auto index = [&](const Node &node) -> int { return node.x * n + node.y;};
        std::queue<std::pair<Node, Node>> queue1;

        dp[index(start)][index(initBox)] = 0;   // 初始状态的推动次数为0
        queue1.emplace(start, initBox);
        // queue1:推动箱子前的状态
        // queue2:推动箱子后的状态
        while (!queue1.empty())
        {
            std::queue<std::pair<Node, Node>> queue2;
            while (!queue1.empty())
            {
                auto [player, box] = queue1.front();
                queue1.pop();

                int playerIndex = index(player);
                int boxIndex = index(box);

                // 箱子已经被推到目标处
                if (grid[box.x][box.y] == 'T')
                {
                    return dp[playerIndex][boxIndex];
                }

                // 玩家向四个方向移动到另一个状态
                for (int i = 0; i < 4; ++i)
                {
                    Node playerNext(player.x + dir[i][0], player.y + dir[i][1]);
                    // 下一个位置不合法
                    if (!isValid(playerNext))
                    {
                        continue;
                    }

                    int playerNextIndex = index(playerNext);
                    // 下一个位置是箱子的位置，推动箱子
                    if (playerNext == box)
                    {
                        Node boxNext(box.x + dir[i][0], box.y + dir[i][1]);
                        playerNextIndex = index(playerNext);
                        int boxNextIndex = index(boxNext);

                        // 箱子位置不合法
                        if (!isValid(boxNext) || dp[playerNextIndex][boxNextIndex] <= dp[playerIndex][boxIndex] + 1)
                        {
                            continue;
                        }

                        dp[playerNextIndex][boxNextIndex] = dp[playerIndex][boxIndex] + 1;
                        queue2.emplace(playerNext, boxNext);
                    }
                    // 下一个位置不是箱子
                    else
                    {
                        // 下一个状态已经访问过
                        if (dp[playerNextIndex][boxIndex] <= dp[playerIndex][boxIndex])
                        {
                            continue;
                        }
                        dp[playerNextIndex][boxIndex] = dp[playerIndex][boxIndex];
                        queue1.emplace(playerNext, box);
                    }
                }
            }
            // 推动箱子前的所有状态都遍历完
            queue1.swap(queue2);
        }
        return -1;
    }
};


int main()
{
    Solution2 solution;
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