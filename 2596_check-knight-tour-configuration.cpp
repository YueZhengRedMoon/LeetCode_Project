#include <iostream>
#include <vector>

class Solution
{
public:
    bool checkValidGrid(std::vector<std::vector<int>> &grid)
    {
        if (grid[0][0] != 0)
            return false;

        int n = grid.size();
        std::vector<std::pair<int, int>> track(n * n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                track[grid[i][j]] = {i, j};
            }
        }

        for (int i = 1; i < n * n; ++i)
        {
            int dx = std::abs(track[i].first - track[i - 1].first);
            int dy = std::abs(track[i].second - track[i - 1].second);
            if (!(dx == 1 && dy == 2) && !(dx == 2 && dy == 1))
                return false;
        }

        return true;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
