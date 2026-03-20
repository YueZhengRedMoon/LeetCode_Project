#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> minAbsDiff(std::vector<std::vector<int>>& grid, int k)
    {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<int>> ans(m - k + 1, std::vector<int>(n - k + 1));

        if (k == 1)
        {
            return ans;
        }

        std::vector<int> elems(k * k);  // 子矩阵中的元素
        for (int i = 0; i < m - k + 1; ++i)
        {
            for (int j = 0; j < n - k + 1; ++j)
            {
                int e = 0;
                for (int x = i; x < i + k; ++x)
                {
                    for (int y = j; y < j + k; ++y)
                    {
                        elems[e++] = grid[x][y];
                    }
                }

                std::sort(elems.begin(), elems.end());
                int minAbsDiff = INT_MAX;
                for (e = 1; e < k * k; ++e)
                {
                    if (elems[e] - elems[e - 1] != 0)
                    {
                        minAbsDiff = std::min(minAbsDiff, elems[e] - elems[e - 1]);
                    }
                }
                ans[i][j] = minAbsDiff == INT_MAX ? 0 : minAbsDiff;
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