#include <iostream>
#include <vector>

class Solution
{
public:
    int countServers(std::vector<std::vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        std::vector<int> rowCnt(m, 0), colCnt(n, 0);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                rowCnt[i] += grid[i][j];
                colCnt[j] += grid[i][j];
            }
        }
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] && (rowCnt[i] > 1 || colCnt[j] > 1))
                    ++ans;
            }
        }
        return ans;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
