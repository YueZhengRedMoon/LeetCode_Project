#include <iostream>
#include <vector>
#include "../debug/debug.h"

class Solution
{
public:
    std::vector<std::vector<int>> multiply(std::vector<std::vector<int>> &mat1, std::vector<std::vector<int>> &mat2)
    {
        int m = mat1.size(), n = mat2[0].size(), k = mat2.size();
        std::vector<bool> isZeroRow(m, true), isZeroCol(n, true);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < k; ++j)
            {
                if (mat1[i][j] != 0)
                {
                    isZeroRow[i] = false;
                    break;
                }
            }
        }
        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < k; ++i)
            {
                if (mat2[i][j] != 0)
                {
                    isZeroCol[j] = false;
                    break;
                }
            }
        }

        std::vector<std::vector<int>> ans(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
        {
            if (isZeroRow[i])
                continue;

            for (int j = 0; j < n; ++j)
            {
                if (isZeroCol[j])
                    continue;

                for (int t = 0; t < k; ++t)
                {
                    ans[i][j] += mat1[i][t] * mat2[t][j];
                }
            }
        }

        return ans;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> mat1 = {{1,0,0},{-1,0,3}};
    std::vector<std::vector<int>> mat2 = {{7,0,0},{0,0,0},{0,0,1}};
    std::vector<std::vector<int>> ans = solution.multiply(mat1, mat2);
    debug::printVector2D(ans);
    return 0;
}
