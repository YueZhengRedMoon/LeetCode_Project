#include <iostream>
#include <vector>
#include <functional>
#include <queue>

class Solution1
{
public:
    int minimumEffortPath(std::vector<std::vector<int>> &heights)
    {
        const int dir[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
        int rows = heights.size(), cols = heights[0].size(), maxHeight = 0, minHeight = 0x3f3f3f3f, ans = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (heights[i][j] > maxHeight)
                    maxHeight = heights[i][j];
                if (heights[i][j] < minHeight)
                    minHeight = heights[i][j];
            }
        }

        int lower = 0, upper = maxHeight - minHeight;
        while (lower <= upper)
        {
            int mid = (lower + upper) / 2;
            std::queue<std::pair<int, int>> queue;
            queue.emplace(0, 0);
            std::vector<bool> visited(rows * cols, false);
            visited[0] = true;
            while (!queue.empty())
            {
                auto [x, y] = queue.front();
                queue.pop();
                for (int i = 0; i < 4; ++i)
                {
                    int nx = x + dir[i][0], ny = y + dir[i][1];
                    if (0 <= nx && nx < rows && 0 <= ny && ny < cols && !visited[nx * cols + ny] &&
                        std::abs(heights[x][y] - heights[nx][ny]) <= mid)
                    {
                        queue.emplace(nx, ny);
                        visited[nx * cols + ny] = true;
                    }
                }
            }
            if (visited.back())
            {
                ans = mid;
                upper = mid - 1;
            }
            else
            {
                lower = mid + 1;
            }
        }

        return ans;
    }
};

namespace TimeLimit
{
    class Solution
    {
    public:
        int minimumEffortPath(std::vector<std::vector<int>> &heights)
        {
            const int dir[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
            int rows = heights.size(), cols = heights[0].size(), ans = 0x3f3f3f3f;
            std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
            std::function<void(int, int, int)> dfs = [&](int x, int y, int effort) {
                if (x == rows - 1 && y == cols - 1)
                {
                    if (effort < ans)
                        ans = effort;
                    return;
                }

                visited[x][y] = true;
                for (int i = 0; i < 4; ++i)
                {
                    int nx = x + dir[i][0], ny = y + dir[i][1];
                    if (0 <= nx && nx < rows && 0 <= ny && ny < cols && !visited[nx][ny])
                    {
                        int abs = std::abs(heights[x][y] - heights[nx][ny]);
                        if (abs <= ans)
                        {
                            dfs(nx, ny, std::max(abs, effort));
                        }
                    }
                }
                visited[x][y] = false;
            };
            dfs(0, 0, 0);
            return ans;
        }
    };
}

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
