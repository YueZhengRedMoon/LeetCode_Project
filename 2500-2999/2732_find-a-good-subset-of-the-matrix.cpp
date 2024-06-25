#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    std::vector<int> goodSubsetofBinaryMatrix(std::vector<std::vector<int>>& grid)
    {
        std::unordered_map<int, int> mask_to_idx;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i)
        {
            int mask = 0;
            for (int j = 0; j < n; ++j)
            {
                mask |= grid[i][j] << j;
            }
            if (mask == 0)
            {
                return {i};
            }
            mask_to_idx[mask] = i;
        }

        for (auto [x, i] : mask_to_idx)
        {
            for (auto [y, j] : mask_to_idx)
            {
                if ((x & y) == 0)
                    return {std::min(i, j), std::max(i, j)};
            }
        }

        return {};
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
