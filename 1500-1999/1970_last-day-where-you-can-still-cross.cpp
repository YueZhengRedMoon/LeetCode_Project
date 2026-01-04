#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

class UnionFind
{
public:
    UnionFind(int n) : fa(n)
    {
        std::iota(fa.begin(), fa.end(), 0);
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        else
            return fa[x] = find(fa[x]);
    }

    bool isSame(int x, int y)
    {
        return find(x) == find(y);
    }

    void merge(int from, int to)
    {
        int x = find(from), y = find(to);
        fa[x] = y;
    }

private:
    std::vector<int> fa;
};

class Solution
{
public:
    int latestDayToCross(int m, int n, std::vector<std::vector<int>>& cells)
    {
        const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int top = m * n, bottom = m * n + 1;
        UnionFind uf(m * n + 2);
        std::vector<std::vector<int8_t>> land(m, std::vector<int8_t>(n));

        for (int day = (int) cells.size() - 1; ;--day)
        {
            int r = cells[day][0] - 1, c = cells[day][1] - 1;
            int v = r * n + c;
            land[r][c] = 1; // 变成陆地

            if (r == 0)
            {
                uf.merge(v, top);   // 与最上边相连
            }
            if (r == m - 1)
            {
                uf.merge(v, bottom);    // 与最下边相连
            }

            for (int i = 0; i < 4; ++i)
            {
                int x = r + dir[i][0], y = c + dir[i][1];
                if (0 <= x && x < m && 0 <= y && y < n && land[x][y])
                {
                    uf.merge(v, x * n + y);
                }
            }

            if (uf.isSame(top, bottom)) // 最上边和最下边连通
            {
                return day;
            }
        }
    }
};


namespace TimeLimit
{
    class Solution
    {
    public:
        int latestDayToCross(int row, int col, std::vector<std::vector<int>>& cells)
        {
            const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

            // 检查经过cells[0, i]中的地格被淹没后，能否只经过陆地格子能从最 上面 一行走到最 下面 一行
            auto check = [&](int i) -> bool {
                std::vector<std::vector<int>> grid(row, std::vector<int>(col, 0));
                for (int j = 0; j <= i; ++j)
                {
                    grid[cells[j][0] - 1][cells[j][1] - 1] = 1;
                }

                std::queue<std::pair<int, int>> q;
                for (int y = 0; y < col; ++y)
                {
                    if (grid[0][y] == 0)
                    {
                        q.emplace(0, y);
                    }
                }

                while (!q.empty())
                {
                    auto [x, y] = q.front();
                    q.pop();

                    if (x == row - 1)
                    {
                        return true;
                    }

                    grid[x][y] = 2; // 标记为已访问过

                    for (int j = 0; j < 4; ++j)
                    {
                        int nx = x + dir[j][0], ny = y + dir[j][1];
                        if (0 <= nx && nx < row && 0 <= ny && ny < col && grid[nx][ny] == 0)
                        {
                            q.emplace(nx, ny);
                        }
                    }
                }

                return false;
            };

            int l = 0, r = cells.size(), ans = 0;
            while (l < r)
            {
                int mid = (l + r) / 2;
                if (check(mid))
                {
                    ans = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid;
                }
            }
            return ans;
        }
    };
}

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}