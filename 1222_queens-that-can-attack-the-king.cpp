#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> queensAttacktheKing(std::vector<std::vector<int>> &queens, std::vector<int> &king)
    {
        char board[8][8]{};
        for (const std::vector<int> &queen : queens)
        {
            board[queen[0]][queen[1]] = 'Q';
        }
        const int dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < 8; ++i)
        {
            int x = king[0] + dir[i][0], y = king[1] + dir[i][1];
            while (0 <= x && x < 8 && 0 <= y && y < 8)
            {
                if (board[x][y] == 'Q')
                {
                    ans.push_back({x, y});
                    break;
                }
                x += dir[i][0];
                y += dir[i][1];
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
