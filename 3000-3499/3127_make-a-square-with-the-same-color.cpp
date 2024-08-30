#include <iostream>
#include <vector>

class Solution
{
public:
    bool canMakeSquare(std::vector<std::vector<char>>& grid)
    {
        if (check(grid))
            return true;

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                char c = grid[i][j];
                grid[i][j] = c == 'W' ? 'B' : 'W';
                if (check(grid))
                    return true;
                grid[i][j] = c;
            }
        }

        return false;
    }

private:
    bool check(const std::vector<std::vector<char>>& g)
    {
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 1; ++j)
            {
                if (g[i][j] == g[i + 1][j] && g[i][j] == g[i][j + 1] && g[i][j] == g[i + 1][j + 1])
                    return true;
            }
        }
        return false;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
