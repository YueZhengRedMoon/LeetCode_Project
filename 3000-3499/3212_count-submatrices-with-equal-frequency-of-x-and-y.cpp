#include <iostream>
#include <vector>
#include <array>

class Solution
{
public:
    int numberOfSubmatrices(std::vector<std::vector<char>>& grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        std::vector<std::vector<std::pair<int, int>>> prefix(m + 1, std::vector<std::pair<int, int>>(n + 1));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                prefix[i + 1][j + 1].first = prefix[i + 1][j].first + prefix[i][j + 1].first - prefix[i][j].first + (grid[i][j] == 'X');
                prefix[i + 1][j + 1].second = prefix[i + 1][j].second + prefix[i][j + 1].second - prefix[i][j].second + (grid[i][j] == 'Y');

                if (prefix[i + 1][j + 1].first && prefix[i + 1][j + 1].first == prefix[i + 1][j + 1].second)
                {
                    ++ans;
                }
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int numberOfSubmatrices(std::vector<std::vector<char>>& grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        std::vector<std::array<int, 2>> colCnt(n);
        for (int i = 0; i < m; ++i)
        {
            int cntX = 0, cntY = 0;
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 'X')
                {
                    ++colCnt[j][0];
                }
                else if (grid[i][j] == 'Y')
                {
                    ++colCnt[j][1];
                }

                cntX += colCnt[j][0];
                cntY += colCnt[j][1];
                if (cntX && cntX == cntY)
                {
                    ++ans;
                }
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