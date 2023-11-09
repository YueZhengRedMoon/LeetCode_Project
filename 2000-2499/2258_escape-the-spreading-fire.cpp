#include <iostream>
#include <vector>
#include <queue>
#include "debug.h"

class Solution
{
public:
    int maximumMinutes(std::vector<std::vector<int>> &grid)
    {
        const int inf = 1e9;
        const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int m = grid.size(), n = grid[0].size();
        auto isGrass = [&](int x, int y) -> bool { return 0 <= x && x < m && 0 <= y && y < n && grid[x][y] == 0; };

        // fireReach[x][y]:火灾蔓延到(x, y)需要的最短时间
        std::vector<std::vector<int>> fireReach(m, std::vector<int>(n, inf));
        std::queue<std::pair<int, int>> queue;
        for (int x = 0; x < m; ++x)
        {
            for (int y = 0; y < n; ++y)
            {
                if (grid[x][y] == 1)
                {
                    fireReach[x][y] = 0;
                    queue.emplace(x, y);
                }
            }
        }
        // BFS计算火灾蔓延到每个格子需要的时间
        int maxReachTime = 0;
        while (!queue.empty())
        {
            auto [x, y] = queue.front();
            queue.pop();
            maxReachTime = fireReach[x][y];
            int reachTime = maxReachTime + 1;
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0], ny = y + dir[i][1];
                if (isGrass(nx, ny) && reachTime < fireReach[nx][ny])
                {
                    fireReach[nx][ny] = reachTime;
                    queue.emplace(nx, ny);
                }
            }
        }
        debug::printVector2D(fireReach, inf);

        // arriveTime[x][y]:在起点停留time后，到达(x, y)时的最少时间
        std::vector<std::vector<int>> arriveTime(m, std::vector<int>(n));
        // 检查在起点停留time后还能否到达安全屋
        auto check = [&](int time) -> bool {
            if (fireReach[0][0] <= time)
                return false;

            for (int x = 0; x < m; ++x)
            {
                for (int y = 0; y < n; ++y)
                {
                    arriveTime[x][y] = inf;
                }
            }
            arriveTime[0][0] = time;

            std::queue<std::pair<int, int>> q;
            q.emplace(0, 0);
            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();
                int newArriveTime = arriveTime[x][y] + 1;
                for (int i = 0; i < 4; ++i)
                {
                    int nx = x + dir[i][0], ny = y + dir[i][1];
                    if (isGrass(nx, ny) && newArriveTime < arriveTime[nx][ny])
                    {
                        if (nx == m - 1 && ny == n - 1) // 下一个位置是安全屋
                        {
                            if (newArriveTime <= fireReach[nx][ny])   // 可以与火同时到达安全屋
                                return true;
                        }
                        else
                        {
                            if (newArriveTime < fireReach[nx][ny])
                            {
                                arriveTime[nx][ny] = newArriveTime;
                                q.emplace(nx, ny);
                            }
                        }
                    }
                }
            }

            return false;
        };

        // 二分查找在初始位置可以停留的最长时间
        int lower = 0, upper = maxReachTime, ans = -1;
        while (lower <= upper)
        {
            int mid = (lower + upper) / 2;
            if (check(mid))
            {
                ans = mid;
                lower = mid + 1;
            }
            else
            {
                upper = mid - 1;
            }
        }

        return ans >= maxReachTime ? inf : ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{0,2,0,0,0,0,0},
                                          {0,0,0,2,2,1,0},
                                          {0,2,0,0,1,2,0},
                                          {0,0,2,2,2,0,2},
                                          {0,0,0,0,0,0,0}};
    int ans = solution.maximumMinutes(grid);
    logObj(ans);
    return 0;
}
