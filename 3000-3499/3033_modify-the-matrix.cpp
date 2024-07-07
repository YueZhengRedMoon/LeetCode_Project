#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> modifiedMatrix(std::vector<std::vector<int>>& matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        std::vector<int> colMax(n, -1);
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] > colMax[j])
                    colMax[j] = matrix[i][j];
            }
        }
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == -1)
                    matrix[i][j] = colMax[j];
            }
        }
        return matrix;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
