#include <iostream>
#include <vector>
#include <bitset>

class Solution
{
public:
    bool isValidSudoku(std::vector<std::vector<char>> &board)
    {
        std::bitset<9> row[9], col[9], sudoku[9];
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (isdigit(board[i][j]))
                {
                    int num = board[i][j] - '0';
                    int sudokuIndex = (i / 3) * 3 + (j / 3);
                    if (row[i][num] || col[j][num] || sudoku[sudokuIndex][num])
                    {
                        return false;
                    }
                    row[i][num] = true;
                    col[j][num] = true;
                    sudoku[sudokuIndex][num] = true;
                }
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}