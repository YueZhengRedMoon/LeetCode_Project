#include <iostream>
#include <vector>

class Solution
{
public:
    // 最大化最小值
    int maximumMinimumPath(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size(), minVal = INT_MAX, maxVal = INT_MIN;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] < minVal)
                    minVal = grid[i][j];
                if (grid[i][j] > maxVal)
                    maxVal = grid[i][j];
            }
        }

        int ans = 0, left = minVal, right = maxVal;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (check(grid, mid))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return ans;
    }

private:
    const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    // 检查在二维矩阵g中，是否可能从起点开始到达终点，使得经过的每个网格的分数都>=minScore
    bool check(const std::vector<std::vector<int>>& g, int minScore)
    {
        if (g[0][0] < minScore)
            return false;

        int m = g.size(), n = g[0].size();
        // score[i][j]:从g[0][0]到达g[i][j]所经过的最小分数
        std::vector<std::vector<int>> score(m, std::vector<int>(n, INT_MAX));
        score[0][0] = g[0][0];
        return dfs(g, 0, 0, score, minScore);
    }

    bool dfs(const std::vector<std::vector<int>>& g, int x, int y, std::vector<std::vector<int>>& score, int minScore)
    {
        int m = g.size(), n = g[0].size();
        if (x == m - 1 && y == n - 1)
            return true;

        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if (0 <= nx && nx < m && 0 <= ny && ny < n && g[nx][ny] >= minScore)
            {
                int s = std::min(score[x][y], g[nx][ny]);
                if (s < score[nx][ny])
                {
                    score[nx][ny] = s;
                    if (dfs(g, nx, ny, score, minScore))
                        return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> grid = {{0,1,0,0,0,1},{0,1,1,0,0,0},{0,0,1,1,0,1},{0,1,1,1,1,0},{1,1,1,1,1,1}};
    int ans = solution.maximumMinimumPath(grid);
    std::cout << ans << std::endl;
    return 0;
}
