#include <iostream>
#include <vector>

class Solution
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