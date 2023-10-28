#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <forward_list>
#include <functional>
#include <numeric>
#include "../debug/debug.h"

class Solution
{
public:
    using Grid = std::vector<std::vector<int>>;
    using Pair = std::pair<int, int>;

    int maximumSafenessFactor(Grid &grid)
    {
        const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        const int inf = 0x3f3f3f3f;
        int n = grid.size();
        std::list<std::queue<Pair>> queues;
        std::unordered_map<int, std::forward_list<Pair>> group;

        Grid dis(n, std::vector<int>(n, inf));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    dis[i][j] = 0;
                    std::queue<Pair> queue;
                    queue.emplace(i, j);
                    queues.push_back(std::move(queue));
                }
            }
        }


        int maxDis = 0;
        while (!queues.empty())
        {
            auto it = queues.begin();
            while (it != queues.end())
            {
                std::queue<Pair> &queue = *it;
                int size = queue.size();
                for (int i = 0; i < size; ++i)
                {
                    auto [x, y] = queue.front();
                    queue.pop();
                    int nextDis = dis[x][y] + 1;
                    for (int i = 0; i < 4; ++i)
                    {
                        int nx = x + dir[i][0], ny = y + dir[i][1];
                        if (0 <= nx && nx < n && 0 <= ny && ny < n && nextDis < dis[nx][ny])
                        {
                            dis[nx][ny] = nextDis;
                            group[nextDis].emplace_front(nx, ny);
                            queue.emplace(nx, ny);
                            if (nextDis > maxDis)
                                maxDis = nextDis;
                        }
                    }
                }
                if (queue.empty())
                {
                    auto eraseIt = it;
                    ++it;
                    queues.erase(eraseIt);
                }
                else
                {
                    ++it;
                }
            }
        }

        // 并查集
        std::vector<int> parent(n * n);
        std::vector<int> rank(n * n, 0);
        std::iota(parent.begin(), parent.end(), 0);
        std::function<int(int)> find = [&](int x) -> int {
            if (parent[x] == x)
                return x;
            return parent[x] = find(parent[x]);
        };
        std::function<void(int, int)> unite = [&](int x, int y) {
            x = find(x);
            y = find(y);
            if (x == y)
                return;

            if (rank[x] < rank[y])
            {
                parent[x] = y;
            }
            else
            {
                parent[y] = x;
                if (rank[x] == rank[y])
                    ++rank[x];
            }
        };

        Grid temp(n, std::vector<int>(n, 0));
        for (int d = maxDis; d > 0; --d)
        {
            for (auto [x, y] : group[d])
            {
                int idx = x * n + y;
                for (int i = 0; i < 4; ++i)
                {
                    int nx = x + dir[i][0], ny = y + dir[i][1];
                    if (0 <= nx && nx < n && 0 <= ny && ny < n && dis[x][y] <= dis[nx][ny])
                    {
                        unite(idx, nx * n + ny);
                    }
                }
            }
            if (find(0) == find(n * n - 1))
                return d;
        }

        return 0;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
                                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
                                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                          {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                          {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                          {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                          {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                                          {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
                                          {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
                                          {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0}};
    int ans = solution.maximumSafenessFactor(grid);
    println(ans);
    return 0;
}