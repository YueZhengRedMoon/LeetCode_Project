#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include "debug.h"

namespace TimeLimit
{
    class Solution1
    {
    public:
        struct Status
        {
            int i;
            int j;
            int dis;

            Status(int i_, int j_, int dis_) : i(i_), j(j_), dis(dis_) {}
        };

        int minimumVisitedCells(std::vector<std::vector<int>>& grid)
        {
            int m = grid.size(), n = grid[0].size();
            const int inf = 0x3f3f3f3f;
            std::vector<std::vector<int>> dis(m, std::vector<int>(n, inf));
            dis[0][0] = 1;
            std::priority_queue<Status, std::vector<Status>, std::function<bool(const Status&, const Status)>>
                    queue([&](const Status& a, const Status& b) -> bool {return a.dis > b.dis;});
            queue.emplace(0, 0, 1);
            while (!queue.empty())
            {
                Status s = queue.top();
                queue.pop();
                if (dis[s.i][s.j] < s.dis)
                    continue;
                int newDis = s.dis + 1;
                for (int i = s.i + 1; i <= std::min(s.i + grid[s.i][s.j], m - 1); ++i)
                {
                    if (newDis < dis[i][s.j])
                    {
                        dis[i][s.j] = newDis;
                        queue.emplace(i, s.j, newDis);
                    }
                }
                for (int j = s.j + 1; j <= std::min(s.j + grid[s.i][s.j], n - 1); ++j)
                {
                    if (newDis < dis[s.i][j])
                    {
                        dis[s.i][j] = newDis;
                        queue.emplace(s.i, j, newDis);
                    }
                }
            }
            return dis[m - 1][n - 1] == inf ? -1 : dis[m - 1][n - 1];
        }
    };

    class Solution2
    {
    public:
        int minimumVisitedCells(std::vector<std::vector<int>>& grid)
        {
            int m = grid.size(), n = grid[0].size();
            const int inf = 0x3f3f3f3f;
            // f[i][j]:从(i, j)到(m-1, n-1)经过的最少格子数
            std::vector<std::vector<int>> f(m, std::vector<int>(n, inf));
            f[m - 1][n - 1] = 1;
            for (int i = m - 1; i >= 0; --i)
            {
                for (int j = n - 1; j >= 0; --j)
                {
                    for (int k = i + 1; k <= std::min(m - 1, i + grid[i][j]); ++k)
                        f[i][j] = std::min(f[i][j], f[k][j] + 1);
                    for (int k = j + 1; k <= std::min(n - 1, j + grid[i][j]); ++k)
                        f[i][j] = std::min(f[i][j], f[i][k] + 1);
                }
            }

            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (f[i][j] >= inf)
                        std::cout << "inf\t";
                    else
                        std::cout << f[i][j] << '\t';
                }
                std::cout << std::endl;
            }

            return f[0][0] >= inf ? -1 : f[0][0];
        }
    };
}

int main()
{
    std::vector<std::vector<int>> grid = {{3,4,2,1},{4,2,3,1},{2,1,0,0},{2,4,0,0}};
    TimeLimit::Solution2 solution;
    int ans = solution.minimumVisitedCells(grid);
    logObj(ans); 
    return 0;
}
