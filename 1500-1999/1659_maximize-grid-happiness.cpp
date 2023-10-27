#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

/** 超时 */
class Solution
{
public:
    enum Status
    {
        EMPTY,
        INTROVERT,
        EXTROVERT
    };

    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount)
    {
        grid = std::vector<std::vector<Status>>(m, std::vector<Status>(n, EMPTY));
        maxHappiness = 0;
        row = m;
        col = n;

        backtracking(0, 0, 0, introvertsCount, extrovertsCount);

        return maxHappiness;
    }

private:
    std::vector<std::vector<Status>> grid;
    int maxHappiness;
    int row;
    int col;

    void backtracking(int i, int j, int happiness, int introverts, int extroverts)
    {
        if (happiness > maxHappiness)
            maxHappiness = happiness;
        if ((introverts == 0 && extroverts == 0) || i == row)
            return;

        int nextI, nextJ;
        if (j == col - 1)
        {
            nextI = i + 1;
            nextJ = 0;
        }
        else
        {
            nextI = i;
            nextJ = j + 1;
        }

        if (introverts > 0)
        {
            int newHappiness = happiness + 120;
            if (i > 0)
            {
                if (grid[i - 1][j] == INTROVERT)
                    newHappiness -= 60;
                else if (grid[i - 1][j] == EXTROVERT)
                    newHappiness -= 10;
            }
            if (j > 0)
            {
                if (grid[i][j - 1] == INTROVERT)
                    newHappiness -= 60;
                else if (grid[i][j - 1] == EXTROVERT)
                    newHappiness -= 10;
            }
            if (newHappiness >= happiness)
            {
                grid[i][j] = INTROVERT;
                backtracking(nextI, nextJ, newHappiness, introverts - 1, extroverts);
            }
        }
        if (extroverts > 0)
        {
            int newHappiness = happiness + 40;
            if (i > 0)
            {
                if (grid[i - 1][j] == INTROVERT)
                    newHappiness -= 10;
                else if (grid[i - 1][j] == EXTROVERT)
                    newHappiness += 40;
            }
            if (j > 0)
            {
                if (grid[i][j - 1] == INTROVERT)
                    newHappiness -= 10;
                else if (grid[i][j - 1] == EXTROVERT)
                    newHappiness += 40;
            }
            if (newHappiness >= happiness)
            {
                grid[i][j] = EXTROVERT;
                backtracking(nextI, nextJ, newHappiness, introverts, extroverts - 1);
            }
        }
        grid[i][j] = EMPTY;
        backtracking(nextI, nextJ, happiness, introverts, extroverts);
    }
};

class Solution2
{
public:
    int getMaxGridHappiness(int row, int col, int introvertsCount, int extrovertsCount)
    {
        m = row;
        n = col;
        tot = std::pow(3, n);   // 每一行的状态总数为3^n

        initData();
        std::memset(d, -1, sizeof(d));

        return dfs(0, 0, introvertsCount, extrovertsCount);
    }

private:
    // 每一行最多有5列，每个单元有3种状态，每行有2^5 = 243种状态，多出一行以便于处理第0行
    static constexpr int T = 243, M = 6, N = 5;
    int m, n, tot;
    int maskBits[T][N]{0};
    int ivCount[T]{0}, evCount[T]{0};
    int innerScore[T]{0}, interScore[T][T]{0};
    int d[N][T][M + 1][M + 1];

    static constexpr int score[3][3] = {
            {0, 0, 0},
            {0, -60, -10},
            {0, -10, 40}
    };

    void initData()
    {
        // 计算行内分数
        for (int mask = 0; mask < tot; ++mask)
        {
            int temp = mask;
            for (int i = 0; i < n; ++i)
            {
                int x = temp % 3;
                maskBits[mask][i] = x;
                temp /= 3;
                // 内向的人
                if (x == 1)
                {
                    ++ivCount[mask];
                    innerScore[mask] += 120;
                }
                    // 外向的人
                else if (x == 2)
                {
                    ++evCount[mask];
                    innerScore[mask] += 40;
                }
                if (i > 0)
                {
                    innerScore[mask] += score[x][maskBits[mask][i - 1]];
                }
            }
        }

        // 计算行间分数
        for (int i = 0; i < tot; ++i)
        {
            for (int j = 0; j < tot; ++j)
            {
                interScore[i][j] = 0;
                for (int k = 0; k < n; ++k)
                {
                    interScore[i][j] += score[maskBits[i][k]][maskBits[j][k]];
                }
            }
        }
    }

    int dfs(int row, int preMask, int iv, int ev)
    {
        if (row == m || (iv == 0 && ev == 0))
            return 0;

        if (d[row][preMask][iv][ev] != -1)
            return d[row][preMask][iv][ev];

        int &res = d[row][preMask][iv][ev];
        res = 0;
        for (int mask = 0; mask < tot; ++mask)
        {
            if (ivCount[mask] > iv || evCount[mask] > ev)
                continue;

            res = std::max(res,
                           dfs(row + 1, mask, iv - ivCount[mask], ev - evCount[mask])
                           + innerScore[mask] + interScore[preMask][mask]);
        }

        return res;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
