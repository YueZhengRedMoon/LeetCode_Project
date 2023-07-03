#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    std::vector<std::vector<int>> candyCrush(std::vector<std::vector<int>> &board)
    {
        m = board.size(), n = board[0].size();
        bool isStable;
        do
        {
            isStable = mark(board);
            if (!isStable)
            {
                crush(board);
            }
        } while (!isStable);
        return board;
    }

private:
    int m;
    int n;

    // 标记将要被粉碎的糖果，如果没有糖果被标记，则返回true。
    // 通过将board[i][j]标记为负数，表示其将被粉碎
    bool mark(std::vector<std::vector<int>> &board)
    {
        bool isStable = true;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == 0) continue;

                int absCenter = std::abs(board[i][j]);

                if (j - 1 >= 0 && j + 1 < n)
                {
                    int absLeft = std::abs(board[i][j - 1]), absRight = std::abs(board[i][j + 1]);
                    if (absLeft == absCenter && absCenter == absRight)
                    {
                        board[i][j - 1] = -absLeft;
                        board[i][j] = -absCenter;
                        board[i][j + 1] = -absRight;
                        isStable = false;
                    }
                }

                if (i - 1 >= 0 && i + 1 < m)
                {
                    int absUp = std::abs(board[i - 1][j]), absDown = std::abs(board[i + 1][j]);
                    if (absUp == absCenter && absCenter == absDown)
                    {
                        board[i - 1][j] = -absUp;
                        board[i][j] = -absCenter;
                        board[i + 1][j] = -absDown;
                        isStable = false;
                    }
                }
            }
        }
        return isStable;
    }

    // 粉碎被标记的糖果
    void crush(std::vector<std::vector<int>> &board)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int i = m - 1, k = m - 2; i >= 0; --i)
            {
                if (board[i][j] < 0)
                {
                    board[i][j] = 0;
                    for (k = std::min(k, i - 1); k >= 0; --k)
                    {
                        if (board[k][j] > 0)
                        {
                            board[i][j] = board[k][j];
                            board[k][j] = -board[k][j];
                            --k;
                            break;
                        }
                    }
                }
                else if (board[i][j] == 0)
                {
                    break;
                }
            }
        }
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> board = {{1, 2, 3, 4, 5},
                                           {2, 2, 2, 4, 1},
                                           {3, 2, 4, 4, 5},
                                           {3, 2, 1, 2, 3},
                                           {3, 1, 1, 4, 3}};
    solution.candyCrush(board);
    debug::printVector2D(board);

//    solution.m = board.size();
//    solution.n = board[0].size();
//
//    println("mark:");
//    solution.mark(board);
//    debug::printVector2D(board);
//
//    println("\ncrush:");
//    solution.crush(board);
//    debug::printVector2D(board);
    return 0;
}