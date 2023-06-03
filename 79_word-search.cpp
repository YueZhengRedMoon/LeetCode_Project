#include <iostream>
#include <vector>

class Solution
{
public:
    using Board = std::vector<std::vector<char>>;

    bool exist(Board &board, std::string word)
    {
        m = board.size();
        n = board[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == word[0])
                {
                    if (dfs(board, visited, i, j, word, 1))
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

private:
    const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int m;
    int n;

    bool dfs(Board &board, std::vector<std::vector<bool>> &visited, int x, int y,
             const std::string &word, int index)
    {
        if (index == word.size())
        {
            return true;
        }

        visited[x][y] = true;
        for (int i = 0; i < 4; ++i)
        {
            int nextX = x + dir[i][0];
            int nextY = y + dir[i][1];
            if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n
                && !visited[nextX][nextY] && board[nextX][nextY] == word[index])
            {
                if (dfs(board, visited, nextX, nextY, word, index + 1))
                {
                    return true;
                }
            }
        }
        visited[x][y] = false;
        return false;
    }
};

int main()
{
    Solution solution;
    std::cout << std::boolalpha;
    std::vector<std::vector<char>> board2 = {{'A', 'B', 'C', 'E'},
                                             {'S', 'F', 'C', 'S'},
                                             {'A', 'D', 'E', 'E'}};
    bool ans2 = solution.exist(board2, "SEE");
    std::cout <<  ans2 << std::endl;

    std::vector<std::vector<char>> board1 = {{'A','B','C','E'},
                                            {'S','F','C','S'},
                                            {'A','D','E','E'}};
    bool ans1 = solution.exist(board1, "ABCCED");
    std::cout <<  ans1 << std::endl;
    return 0;
}
