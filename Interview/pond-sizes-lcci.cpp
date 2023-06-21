#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Solution
{
public:
    std::vector<int> pondSizes(std::vector<std::vector<int>> &land)
    {
        row = land.size();
        col = land[0].size();
        std::vector<int> ans;

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (land[i][j] == 0)
                {
                    int cnt = bfs(land, i, j);
                    ans.push_back(cnt);
                }
            }
        }

        std::sort(ans.begin(), ans.end());
        return ans;
    }

private:
    int row;
    int col;
    const int dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},
                           {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    int bfs(std::vector<std::vector<int>> &land, int sx, int sy)
    {
        int cnt = 1;
        std::queue<std::pair<int, int>> queue;
        land[sx][sy] = 1;
        queue.emplace(sx, sy);
        while (!queue.empty())
        {
            auto [x, y] = queue.front();
            queue.pop();

            for (int i = 0; i < 8; ++i)
            {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                if (0 <= nx && nx < row && 0 <= ny && ny < col && land[nx][ny] == 0)
                {
                    land[nx][ny] = 1;
                    ++cnt;
                    queue.emplace(nx, ny);
                }
            }
        }
        return cnt;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> land = {{0,2,1,0},{0,1,0,1},{1,1,0,1},{0,1,0,1}};
    std::vector<int> ans = solution.pondSizes(land);
    for (int size : ans)
    {
        std::cout << size << ' ';
    }
    std::cout << std::endl;
    return 0;
}