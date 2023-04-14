#include <iostream>
#include <vector>
#include <sstream>

/** 错误 */
class Solution
{
public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        // 有几个皇后影响了该位置
        std::vector<std::vector<int>> chessboard(n, std::vector<int>(n, 0));
        // 是否放置了皇后
        std::vector<std::vector<bool>> placed(n, std::vector<bool>(n, false));
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        dfs(chessboard, placed, visited, n, 0);
        return solutions;
    }

private:
    std::vector<std::vector<std::string>> solutions;

    void dfs(std::vector<std::vector<int>> &chessboard, std::vector<std::vector<bool>> &placed,
             std::vector<std::vector<bool>> &visited,
             int n, int numPlaced)
    {
        if (numPlaced == n)
        {
            std::vector<std::string> solution;
            solution.reserve(n);
            for (int i = 0; i < n; ++i)
            {
                std::ostringstream stream;
                for (int j = 0; j < n; ++j)
                {
                    if (placed[i][j])
                    {
                        stream << 'Q';
                        visited[i][j] = true;
                    }
                    else
                    {
                        stream << '.';
                    }
                }
                solution.push_back(stream.str());
            }
            solutions.push_back(solution);
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (chessboard[i][j] == 0 && !visited[i][j])
                {
                    updateStatus(chessboard, i, j, n, 1);
                    placed[i][j] = true;
                    ++chessboard[i][j];
                    dfs(chessboard, placed, visited, n, numPlaced + 1);
                    updateStatus(chessboard, i, j, n, -1);
                    --chessboard[i][j];
                    placed[i][j] = false;
                }
            }
        }
    }

    void updateStatus(std::vector<std::vector<int>> &chessboard, int x, int y, int n, int delta)
    {
        for(int i = 0; i < n; ++i)
        {
            if (i != y)
            {
                chessboard[x][i] += delta;
            }
            if (i != x)
            {
                chessboard[i][y] += delta;
            }
        }

        for (int i = x + 1, j = y + 1; i < n && j < n; ++i, ++j)
        {
            chessboard[i][j] += delta;
        }


        for (int i = x + 1, j = y - 1; i < n && j >= 0; ++i, --j)
        {
            chessboard[i][j] += delta;
        }

        for (int i = x - 1, j = y + 1; i >= 0 && j < n; --i, ++j)
        {
            chessboard[i][j] += delta;
        }

        for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j)
        {
            chessboard[i][j] += delta;
        }
    }
};

class Solution2
{
public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        std::vector<std::string> chessboard(n, std::string(n, '.'));
        backtracking(n, 0, chessboard);
        return solutions;
    }

private:
    std::vector<std::vector<std::string>> solutions;

    void backtracking(int n, int row, std::vector<std::string> &chessboard)
    {
        if (row == n)
        {
            solutions.push_back(chessboard);
            return;
        }

        for (int col = 0; col < n; ++col)
        {
            if (isValid(row, col, chessboard, n))
            {
                chessboard[row][col] = 'Q';
                backtracking(n, row + 1, chessboard);
                chessboard[row][col] = '.';
            }
        }
    }

    bool isValid(int row, int col, std::vector<std::string> &chessboard, int n)
    {
        // 检查上方
        for (int i = row - 1; i >= 0; --i)
            if (chessboard[i][col] == 'Q')  return false;

        // 检查左上方
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
            if (chessboard[i][j] == 'Q') return false;

        // 检查右上方
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
            if (chessboard[i][j] == 'Q') return false;

        return true;
    }
};

int main()
{
    int n;
    std::cin >> n;
    Solution2 solution;
    std::vector<std::vector<std::string>> solutions = solution.solveNQueens(n);
    for (const auto &chessboard : solutions)
    {
        for (const auto &row : chessboard)
        {
            std::cout << row << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
