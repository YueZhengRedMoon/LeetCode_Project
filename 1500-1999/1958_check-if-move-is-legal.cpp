#include <iostream>
#include <vector>

class Solution
{
public:
    bool checkMove(std::vector<std::vector<char>>& board, int rMove, int cMove, char color)
    {
        int m = board.size(), n = board[0].size();
        char anotherColor = color == 'W' ? 'B' : 'W';
        const int dir[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1},
                               {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        board[rMove][cMove] = color;
        for (int i = 0; i < 8; ++i)
        {
            int x = rMove + dir[i][0], y = cMove + dir[i][1];
            bool isVisitAnotherColor = false;
            while (0 <= x && x < m && 0 <= y && y < n && board[x][y] == anotherColor)
            {
                x += dir[i][0];
                y += dir[i][1];
                isVisitAnotherColor = true;
            }
            if (0 <= x && x < m && 0 <= y && y < n && board[x][y] == color && isVisitAnotherColor)
                return true;
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
