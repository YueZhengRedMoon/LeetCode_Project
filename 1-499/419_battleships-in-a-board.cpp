#include <iostream>
#include <vector>

class Solution
{
public:
    int countBattleships(std::vector<std::vector<char>>& board)
    {
        int m = board.size(), n = board[0].size(), ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ans += board[i][j] == 'X' && (i == 0 || board[i - 1][j] == '.') && (j == 0 || board[i][j - 1] == '.');
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
