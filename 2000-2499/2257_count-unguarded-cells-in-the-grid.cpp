#include <iostream>
#include <vector>

class Solution
{
public:
    int countUnguarded(int m, int n, std::vector<std::vector<int>>& guards, std::vector<std::vector<int>>& walls)
    {
        std::vector<std::vector<int>> isGuarded(m, std::vector<int>(n, 0)); // 0:未被保卫，1:被保卫, 2:存在墙或者警卫
        const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // 标记存在警卫和墙的地方
        for (const std::vector<int>& w : walls)
        {
            int x = w[0], y = w[1];
            isGuarded[x][y] = 2;
        }
        for (const std::vector<int>& g : guards)
        {
            int x = g[0], y = g[1];
            isGuarded[x][y] = 2;
        }

        auto guard = [&](int x, int y) {
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0], ny = y + dir[i][1];
                while (0 <= nx && nx < m && 0 <= ny && ny < n && isGuarded[nx][ny] != 2)
                {
                    isGuarded[nx][ny] = 1;
                    nx += dir[i][0];
                    ny += dir[i][1];
                }
            }
        };

        for (const std::vector<int>& g : guards)
        {
            int x = g[0], y = g[1];
            guard(x, y);
        }

        int ans = 0;
        for (int x = 0; x < m; ++x)
        {
            for (int y = 0; y < n; ++y)
            {
                if (!isGuarded[x][y])
                    ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}