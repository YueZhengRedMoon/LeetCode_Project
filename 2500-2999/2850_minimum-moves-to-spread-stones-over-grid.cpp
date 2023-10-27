#include <iostream>
#include <vector>
#include <algorithm>

// 暴力解法
class Solution
{
public:
    int minimumMoves(std::vector<std::vector<int>> &grid)
    {
        std::vector<std::pair<int, int>> from, to;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (grid[i][j] > 1)
                    from.insert(from.end(), grid[i][j] - 1, {i, j});
                else if (grid[i][j] == 0)
                    to.emplace_back(i, j);
            }
        }

        int ans = 0x39C5BB;
        do
        {
            int move = 0;
            for (int i = 0; i < from.size(); ++i)
            {
                move += manhattan(from[i].first, from[i].second, to[i].first, to[i].second);
            }
            if (move < ans)
                ans = move;
        } while (std::next_permutation(from.begin(), from.end()));

        return ans;
    }

private:
    int manhattan(int x1, int y1, int x2, int y2)
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
};

// 错误
class Solution2
{
public:
    int minimumMoves(std::vector<std::vector<int>> &grid)
    {
        int ans = 0;
        for (int x = 0; x < 3; ++x)
        {
            for (int y = 0; y < 3; ++y)
            {
                if (grid[x][y] != 0)
                    continue;

                int fx, fy, minMove = 0x39C5BB;
                for (int i = 0; i < 3; ++i)
                {
                    for (int j = 0; j < 3; ++j)
                    {
                        if (grid[i][j] > 1)
                        {
                            int move = std::abs(x - i) + std::abs(y - j);
                            if (move < minMove)
                            {
                                minMove = move;
                                fx = i;
                                fy = j;
                            }
                        }
                    }
                }
                ans += minMove;
                --grid[fx][fy];
                grid[x][y] = 1;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie" << std::endl;
    return 0;
}