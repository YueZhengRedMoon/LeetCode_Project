#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int uniquePathsIII(std::vector<std::vector<int>> &grid)
    {
        ans = 0;
        m = grid.size();
        n = grid[0].size();
        count = 1;
        int sx, sy;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    sx = i;
                    sy = j;
                }
                else if (grid[i][j] == 0)
                {
                    ++count;
                }
            }
        }

        dfs(grid, sx, sy, 0);
        return ans;
    }

private:
    const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int ans;
    int m;
    int n;
    int count;

    void dfs(std::vector<std::vector<int>> &grid, int x, int y, int step)
    {
        if (grid[x][y] == 2)
        {
            if (step == count)
                ++ans;
            return;
        }

        ++step;
        grid[x][y] = 3;
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (0 <= nx && nx < m && 0 <= ny && ny < n && (grid[nx][ny] == 0 || grid[nx][ny] == 2))
            {
                int temp = grid[nx][ny];
                dfs(grid, nx, ny, step);
                grid[nx][ny] = temp;
            }
        }
    }
};

class Solution2
{
public:
    int uniquePathsIII(std::vector<std::vector<int>> &grid)
    {
        r = grid.size();
        c = grid[0].size();
        int si = 0, sj = 0, st = 0;
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                if (grid[i][j] == 0 || grid[i][j] == 2)
                {
                    st |= (1 << (i * c + j));
                }
                else if (grid[i][j] == 1)
                {
                    si = i;
                    sj = j;
                }
            }
        }

        return dfs(grid, si, sj, st);
    }

private:
    int r;
    int c;
    std::unordered_map<int, int> memo;
    const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int dfs(std::vector<std::vector<int>> &grid, int i, int j, int st)
    {
        if (grid[i][j] == 2)
        {
            return st == 0;
        }

        int key = ((i * c + j) << (r * c)) + st;
        auto it = memo.find(key);
        if (it != memo.end())
            return it->second;

        int res = 0;
        for (int k = 0; k < 4; ++k)
        {
            int ni = i + dir[k][0], nj = j + dir[k][1];
            if (ni >= 0 && ni < r && nj >= 0 && nj < c && (st & (1 << (ni * c + nj))) > 0)
            {
                res += dfs(grid, ni, nj, st ^ (1 << (ni * c + nj)));
            }
        }
        return memo[key] = res;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}