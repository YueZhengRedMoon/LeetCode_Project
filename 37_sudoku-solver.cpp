#include <iostream>
#include <vector>
#include <cstring>

class Solution
{
public:
    using Board = std::vector<std::vector<char>>;

    void solveSudoku(Board &board)
    {
        std::memset(rowUsed, 0, sizeof(rowUsed));
        std::memset(colUsed, 0, sizeof(colUsed));
        std::memset(used3x3, 0, sizeof(used3x3));

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                if (std::isdigit(board[i][j]))
                {
                    setUsed(i, j, board[i][j] - '0', true);
                }
            }
        }

        backtracking(board, 0, 0);
    }

private:
    /** rowUsed[i][j]:第i行的数j是否使用过 */
    bool rowUsed[9][10];

    /** colUsed[i][j]:第i列的数j是否使用过 */
    bool colUsed[9][10];

    /** used3x3[i][j]:从上到下从左到右第i个九宫格是否使用过数j */
    bool used3x3[9][10];

    bool backtracking(Board &board, int row, int col)
    {
        // 数字已经填完
        if (row == 9)
        {
            return true;
        }

        // 这一格已经填过
        if (board[row][col] != '.')
        {
            // 这一行已经填满，填写下一行
            if (col == 8)
                return backtracking(board, row + 1, 0);
            // 这一行还没有填满，填写下一列
            else
                return backtracking(board, row, col + 1);
        }

        // 尝试填写1~9
        for (int num = 1; num <= 9; ++num)
        {
            // 在第row行第col列填写num有效
            if (isValid(row, col, num))
            {
                // 填写数字
                board[row][col] = static_cast<char>(num + '0');
                setUsed(row, col, num, true);

                bool findSolution = false;
                // 这一行已经填满，填写下一行
                if (col == 8)
                    findSolution = backtracking(board, row + 1, 0);
                // 这一行还没有填满，填写下一列
                else
                    findSolution = backtracking(board, row, col + 1);

                // 找到解
                if (findSolution)
                    return findSolution;

                // 回溯
                board[row][col] = '.';
                setUsed(row, col, num, false);
            }
        }

        return false;
    }

    inline int get3x3Index(int i, int j)
    {
        return (i / 3) * 3 + (j / 3);
    }

    inline bool isValid(int i, int j, int num)
    {
        return !rowUsed[i][num] && !colUsed[j][num] && !used3x3[get3x3Index(i, j)][num];
    }

    inline void setUsed(int i, int j, int num, bool used)
    {
        rowUsed[i][num] = used;
        colUsed[j][num] = used;
        used3x3[get3x3Index(i, j)][num] = used;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
