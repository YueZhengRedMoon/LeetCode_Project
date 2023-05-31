#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Solution
{
public:
    using Board = std::vector<std::vector<int>>;

    int snakesAndLadders(Board &board)
    {
        n = board.size();
        std::vector<int> minStep(n * n + 1, std::numeric_limits<int>::max());
        minStep[1] = 0;
        std::queue<int> queue;
        queue.push(1);
        while (!queue.empty())
        {
            int cur = queue.front();
            std::cout << cur << std::endl;
            if (cur == n * n)
            {
                return minStep[cur];
            }
            queue.pop();
            int step = minStep[cur] + 1;
            for (int i = 1; i <= 6; ++i)
            {
                int next = std::min(cur + i, n * n);
                int val = getBoardValue(board, next);
                if (val != -1)
                {
                    next = val;
                }
                if (step < minStep[next])
                {
                    queue.push(next);
                    minStep[next] = step;
                }
            }
        }
        return -1;
    }

private:
    int n;

    inline int getBoardValue(Board &board, int i)
    {
        int x = n - ((i - 1) / n) - 1;
        int y;
        if ((i / n) % 2 == 1)
        {
            y = (i - 1) % n;
        }
        else
        {
            y = (n - 1) - (i - 1) % n;
        }
        return board[x][y];
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> board = {{-1,-1,-1,-1,-1,-1},
                                           {-1,-1,-1,-1,-1,-1},
                                           {-1,-1,-1,-1,-1,-1},
                                           {-1,35,-1,-1,13,-1},
                                           {-1,-1,-1,-1,-1,-1},
                                           {-1,15,-1,-1,-1,-1}};
    int ans = solution.snakesAndLadders(board);
    std::cout << ans << std::endl;
    return 0;
}