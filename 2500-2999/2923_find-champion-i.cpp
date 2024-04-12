#include <iostream>
#include <vector>

class Solution
{
public:
    int findChampion(std::vector<std::vector<int>>& grid)
    {
        int n = grid.size();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i != j)
                {
                    grid[j][j] += grid[i][j];
                }
            }
        }
        int ans = -1;
        for (int i = 0; i < n; ++i)
        {
            if (grid[i][i] == 0)
            {
                ans = i;
                break;
            }
        }
        return ans;
    }
};

class Solution2
{
public:
    int findChampion(std::vector<std::vector<int>>& grid)
    {
        int n = grid.size(), ans = 0;
        for (int j = 0; j < n; ++j)
        {
            if (grid[ans][j] == 0)
            {
                // ans打不赢j，那么此前被ans打败的队伍自然更打不赢j了，j成为新的ans
                ans = j;
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
