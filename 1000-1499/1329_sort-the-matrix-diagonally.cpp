#include <iostream>
#include <vector>
#include "debug.h"

class Solution
{
public:
    std::vector<std::vector<int>> diagonalSort(std::vector<std::vector<int>>& mat)
    {
        int m = mat.size(), n = mat[0].size();
        std::vector<int> temp(std::min(m, n));
        for (int i = 0; i < m - 1; ++i)
        {
            int k = 0, x = i, y = 0;
            while (x < m && y < n)
            {
                temp[k++] = mat[x++][y++];
            }
            std::sort(temp.begin(), temp.begin() + k);
            while (k > 0)
            {
                mat[--x][--y] = temp[--k];
            }
        }
        for (int j = 1; j < n - 1; ++j)
        {
            int k = 0, x = 0, y = j;
            while (x < m && y < n)
            {
                temp[k++] = mat[x++][y++];
            }
            std::sort(temp.begin(), temp.begin() + k);
            while (k > 0)
            {
                mat[--x][--y] = temp[--k];
            }
        }
        return mat;
    }
};

int main()
{
    Solution solution;
    std::vector<std::vector<int>> mat = {{93,49,54,89,100,90,63,28,46,67},
                                         {24,97,48,73,62,32,44,100,24,79},
                                         {81,65,45,14,79,86,45,53,68,83},
                                         {29,83,12,90,39,37,4,91,62,43},
                                         {87,19,42,54,30,31,92,24,44,43},
                                         {97,63,90,89,38,73,60,31,20,91},
                                         {93,36,83,50,27,89,27,47,80,5},
                                         {8,99,39,62,24,25,50,58,67,20},
                                         {84,42,21,55,92,48,84,6,79,11}};
    solution.diagonalSort(mat);
    debug::printVector2D(mat);
    return 0;
}
