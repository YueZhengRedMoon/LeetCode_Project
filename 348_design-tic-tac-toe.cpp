#include <iostream>
#include <vector>

class TicTacToe
{
public:
    TicTacToe(int n) :
    rowCount(n),
    colCount(n)
    {
        this->n = n;
    }

    int move(int row, int col, int player)
    {
       if (player == 1)
       {
           if (++rowCount[row].first == n)
               return player;
           if (++colCount[col].first == n)
               return player;
           if (row == col && ++leadingDiagonal.first == n)
               return player;
           if (row == (n - col - 1) && ++subDiagonal.first == n)
               return player;
       }
       else
       {
           if (++rowCount[row].second == n)
               return player;
           if (++colCount[col].second == n)
               return player;
           if (row == col && ++leadingDiagonal.second == n)
               return player;
           if (row == (n - col - 1) && ++subDiagonal.second == n)
               return player;
       }
        return 0;
    }

private:
    int n;
    std::vector<std::pair<int, int>> rowCount, colCount;
    std::pair<int, int> leadingDiagonal;    // 主对角线
    std::pair<int, int> subDiagonal;        // 副对角线
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
