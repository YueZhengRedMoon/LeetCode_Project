#include <iostream>
#include <vector>

class Solution
{
public:
    int countSubmatrices(std::vector<std::vector<int>>& grid, int k)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        // prefix[i+1][j+1]:左上角为grid[0][0],右下角为grid[i][j]的子矩阵的元素和
        std::vector<std::vector<int>> prefix(m + 1, std::vector<int>(n + 1));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                prefix[i + 1][j + 1] = prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j] + grid[i][j];
                if (prefix[i + 1][j + 1] >= k)
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