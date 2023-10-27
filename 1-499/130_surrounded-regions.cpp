#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    using Board = std::vector<std::vector<char>>;
    void solve(Board &board)
    {
        m = board.size();
        n = board[0].size();

        for (int i = 0; i < m; ++i)
        {
            if (board[i][0] == 'O') bfs(board, i, 0);
            if (board[i][n - 1] == 'O') bfs(board, i, n - 1);
        }
        for (int j = 1; j < n - 1; ++j)
        {
            if (board[0][j] == 'O') bfs(board, 0, j);
            if (board[m - 1][j] == 'O') bfs(board, m - 1, j);
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == flag)
                    board[i][j] = 'O';
            }
        }
    }

private:
    int m;
    int n;
    const char flag = '#';
    const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    void bfs(Board &board, int sx, int sy)
    {
        board[sx][sy] = flag;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(sx, sy);
        while (!queue.empty())
        {
            auto [x, y] = queue.front();
            queue.pop();
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O')
                {
                    board[nx][ny] = flag;
                    queue.emplace(nx, ny);
                }
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}