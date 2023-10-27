#include <iostream>
#include <vector>

class Solution
{
public:
    using ChessBoard = std::vector<std::vector<int>>;

    int totalNQueens(int n)
    {
        numSolutions = 0;
        ChessBoard chessBoard(n, std::vector<int>(n, 0));
        backtracking(chessBoard, 0);
        return numSolutions;
    }

private:
    int numSolutions;

    void backtracking(ChessBoard &chessBoard, int row)
    {
        if (row == chessBoard.size())
        {
            ++numSolutions;
            return;
        }

        for (int j = 0; j < chessBoard.size(); ++j)
        {
            if (chessBoard[row][j] == 0)
            {
                updateChessBoard(chessBoard, row, j, 1);
                backtracking(chessBoard, row + 1);
                updateChessBoard(chessBoard, row, j, -1);
            }
        }
    }

    void updateChessBoard(ChessBoard &chessBoard, int row, int col, int delta)
    {
        int size = chessBoard.size();

        // 更新列
        for (int i = 0; i < size; ++i)
            chessBoard[i][col] += delta;

        // 更新行
        for (int j = 0; j < size; ++j)
            chessBoard[row][j] += delta;

        // 更新左上
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            chessBoard[i][j] += delta;

        // 更新右上
        for (int i = row - 1, j = col + 1; i >= 0 && j < size; --i, ++j)
            chessBoard[i][j] += delta;

        // 更新左下
        for (int i = row + 1, j = col - 1; i < size && j >= 0; ++i, --j)
            chessBoard[i][j] += delta;

        // 更新右下
        for (int i = row + 1, j = col + 1; i < size && j < size; ++i, ++j)
            chessBoard[i][j] += delta;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
