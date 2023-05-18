#include <iostream>
#include <vector>

class Solution
{
public:
    using Board = std::vector<std::vector<int>>;

    void gameOfLife(Board &board)
    {
        m = board.size(), n = board[0].size();

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int count = getAliveCeilCount(board, i, j);
                if (board[i][j] == alive)
                {
                    if (count < 2 || count > 3)
                        board[i][j] = willDead;
                }
                else
                {
                    if (count == 3)
                        board[i][j] = willAlive;
                }
            }
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == willAlive)
                    board[i][j] = alive;
                else if (board[i][j] == willDead)
                    board[i][j] = dead;
            }
        }
    }

private:
    const int dir[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0},
                           {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    const int dead = 0;
    const int alive = 1;
    const int willDead = 2;
    const int willAlive = 3;
    int m, n;

    int getAliveCeilCount(Board &board, int x, int y)
    {
        int count = 0;
        for (int i = 0; i < 8; ++i)
        {
            int nextX = x + dir[i][0];
            int nextY = y + dir[i][1];
            if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n &&
                (board[nextX][nextY] == alive || board[nextX][nextY] == willDead))
            {
                ++count;
            }
        }
        return count;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
