#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>

/** 错误 */
class Solution
{
public:
    using Chessboard = std::vector<std::string>;

    int flipChess(Chessboard &chessboard)
    {
        m = chessboard.size();
        n = chessboard[0].size();
        ans = 0;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (chessboard[i][j] == EMPTY)
                {
                    count = 0;
                    chessboard[i][j] = BLACK;
                    dfs(chessboard, i, j);
                    chessboard[i][j] = EMPTY;
                    if (count > ans)
                        ans = count;
                }
            }
        }

        return ans;
    }

private:
    const char BLACK = 'X';
    const char WHITE = 'O';
    const char EMPTY = '.';
    const char FLIP_BLACK = 'x';    // 翻转为黑棋的白棋

    int m, n;
    int ans;
    int count;

    bool isBlack(char chess)
    {
        return chess == BLACK || chess == FLIP_BLACK;
    }

    void flip(Chessboard &chessboard, int bx, int by, int ex, int ey, int dx, int dy, int tex, int tey,
              std::forward_list<std::pair<int, int>> &flipped)
    {
        std::forward_list<std::pair<int, int>> whiteChess;
        bool hasWhite = false, hasEmpty = false;
        int x, y;
        for (x = bx + dx, y = by + dy; x != ex && y != ey; x += dx, y += dy)
        {
            if (chessboard[x][y] == WHITE)
            {
                hasWhite = true;
                whiteChess.emplace_front(x, y);
            }
            else if (chessboard[x][y] == EMPTY)
            {
                hasEmpty = true;
                break;
            }
        }
        x -= dx;
        y -= dy;

        bool canFlip;
        if (hasEmpty)
        {
            canFlip = isBlack(chessboard[x][y]);
        }
        else
        {
            canFlip = isBlack(chessboard[tex][tey]);
        }
        if (hasWhite && canFlip)
        {
            for (auto [wx, wy] : whiteChess)
            {
                ++count;
                flipped.emplace_front(wx, wy);
            }
        }
    }

    void dfs(Chessboard &chessboard, int x, int y)
    {
        std::forward_list<std::pair<int, int>> flipped;

        // 左边
        if (y > 1)
            flip(chessboard, x, y, -1, 0, 0, -1, x, 0, flipped);
        // 右边
        if (y < n - 2)
            flip(chessboard, x, y, -1, n - 1, 0, 1,x, n - 1, flipped);
        // 上边
        if (x > 1)
            flip(chessboard, x, y, 0, -1, -1, 0, 0, y, flipped);
        // 下边
        if (x < m - 2)
            flip(chessboard, x, y, m - 1, -1, 1, 0, m - 1, y, flipped);
        // 左上
        if (y > 1 && x > 1)
            flip(chessboard, x, y, 0, 0, -1, -1, 0, 0,flipped);
        // 右上
        if (y < n - 2 && x > 1)
            flip(chessboard, x, y, 0, n - 1, -1, 1, 0, n - 1, flipped);
        // 左下
        if (y > 1 && x < m - 2)
            flip(chessboard, x, y, m - 1, 0, 1, -1, m - 1, 0, flipped);
        // 右下
        if (y < n - 2 && x < m - 2)
            flip(chessboard, x, y, m - 1, n - 1, 1, 1, m - 1, n - 1, flipped);

        for (auto &pair : flipped)
        {
            dfs(chessboard, pair.first, pair.second);
        }
        for (auto &pair : flipped)
        {
            chessboard[pair.first][pair.second] = WHITE;
        }
    }
};

class Solution2
{
public:
    using Chessboard = std::vector<std::string>;

    int flipChess(Chessboard &chessboard)
    {
        m = chessboard.size(), n = chessboard[0].size();
        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (chessboard[i][j] == '.')
                {
                    int cnt = bfs(chessboard, i, j);
                    if (cnt > ans)
                        ans = cnt;
                }
            }
        }
        return ans;
    }

private:
    const int dirs[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int m, n;

    int bfs(Chessboard chessboard, int px, int py)
    {
        int cnt = 0;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(px, py);
        chessboard[px][py] = 'X';
        while (!queue.empty())
        {
            auto [x, y] = queue.front();
            queue.pop();
            for (int i = 0; i < 8; ++i)
            {
                if (judge(chessboard, x, y, dirs[i][0], dirs[i][1]))
                {
                    int nx = x + dirs[i][0], ny = y + dirs[i][1];
                    while (chessboard[nx][ny] != 'X')
                    {
                        queue.emplace(nx, ny);
                        chessboard[nx][ny] = 'X';
                        nx += dirs[i][0];
                        ny += dirs[i][1];
                        ++cnt;
                    }
                }
            }
        }
        return cnt;
    }

    bool judge(const Chessboard &chessboard, int x, int y, int dx, int dy)
    {
        x += dx;
        y += dy;
        while (0 <= x && x < m && 0 <= y && y < n)
        {
            if (chessboard[x][y] == 'X')
            {
                return true;
            }
            else if (chessboard[x][y] == '.')
            {
                return false;
            }
            x += dx;
            y += dy;
        }
        return false;
    }
};

int main()
{
    Solution2 solution;
    std::vector<std::string> chessboard = {"....X.","....X.","XOOO..","......","......"};
    int ans = solution.flipChess(chessboard);
    std::cout << ans << std::endl;
    return 0;
}