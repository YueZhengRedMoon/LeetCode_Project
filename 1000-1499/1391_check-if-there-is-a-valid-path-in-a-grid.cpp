#include <iostream>
#include <vector>
#include <queue>

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int isValid[7][7][4];   // isValid[i][j][k]:Street i 往k方向(0:上, 1:右, 2:下, 3:左)走是否可以到达Street j
int init = [](){
    isValid[1][1][1] = 1;   // Street 1 往 右 可以到达Street 1
    isValid[1][1][3] = 1;   // Street 1 往 左 可以到达Street 1
    isValid[1][3][1] = 1;   // Street 1 往 右 可以到达Street 3
    isValid[1][4][3] = 1;   // Street 1 往 左 可以到达Street 4
    isValid[1][5][1] = 1;   // Street 1 往 右 可以到达Street 5
    isValid[1][6][3] = 1;   // Street 1 往 左 可以到达Street 6

    isValid[2][2][0] = 1;   // Street 2 往 上 可以到达Street 2
    isValid[2][2][2] = 1;   // Street 2 往 下 可以到达Street 2
    isValid[2][3][0] = 1;   // Street 2 往 上 可以到达Street 3
    isValid[2][4][0] = 1;   // Street 2 往 上 可以到达Street 4
    isValid[2][5][2] = 1;   // Street 2 往 下 可以到达Street 5
    isValid[2][6][2] = 1;   // Street 2 往 下 可以到达Street 6

    isValid[3][2][2] = 1;   // Street 3 往 下 可以到达Street 2
    isValid[3][5][2] = 1;   // Street 3 往 下 可以到达Street 5
    isValid[3][6][2] = 1;   // Street 3 往 下 可以到达Street 6
    isValid[3][1][3] = 1;   // Street 3 往 左 可以到达Street 1
    isValid[3][4][3] = 1;   // Street 3 往 左 可以到达Street 4
    isValid[3][6][3] = 1;   // Street 3 往 左 可以到达Street 6

    isValid[4][1][1] = 1;   // Street 4 往 右 可以到达Street 1
    isValid[4][3][1] = 1;   // Street 4 往 右 可以到达Street 3
    isValid[4][5][1] = 1;   // Street 4 往 右 可以到达Street 5
    isValid[4][2][2] = 1;   // Street 4 往 下 可以到达Street 2
    isValid[4][5][2] = 1;   // Street 4 往 下 可以到达Street 5
    isValid[4][6][2] = 1;   // Street 4 往 下 可以到达Street 6

    isValid[5][2][0] = 1;   // Street 5 往 上 可以到达Street 2
    isValid[5][3][0] = 1;   // Street 5 往 上 可以到达Street 3
    isValid[5][4][0] = 1;   // Street 5 往 上 可以到达Street 4
    isValid[5][1][3] = 1;   // Street 5 往 左 可以到达Street 1
    isValid[5][4][3] = 1;   // Street 5 往 左 可以到达Street 4
    isValid[5][6][3] = 1;   // Street 5 往 左 可以到达Street 6

    isValid[6][2][0] = 1;   // Street 6 往 上 可以到达Street 2
    isValid[6][3][0] = 1;   // Street 6 往 上 可以到达Street 3
    isValid[6][4][0] = 1;   // Street 6 往 上 可以到达Street 4
    isValid[6][1][1] = 1;   // Street 6 往 右 可以到达Street 1
    isValid[6][3][1] = 1;   // Street 6 往 右 可以到达Street 3
    isValid[6][5][1] = 1;   // Street 6 往 右 可以到达Street 5
    return 0;
}();

class Solution
{
public:
    bool hasValidPath(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<bool>> reachable(m, std::vector<bool>(n, false));
        reachable[0][0] = true;
        std::queue<std::pair<int, int>> q;
        q.emplace(0, 0);
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x == m - 1 && y == n - 1)
            {
                break;
            }

            for (int k = 0; k < 4; ++k)
            {
                int nx = x + dir[k][0], ny = y + dir[k][1];
                if (0 <= nx && nx < m && 0 <= ny && ny < n && isValid[grid[x][y]][grid[nx][ny]][k] && !reachable[nx][ny])
                {
                    reachable[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
        }
        return reachable[m - 1][n - 1];
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}