#include <iostream>
#include <vector>

class Solution
{
public:
    void setZeroes(std::vector<std::vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();

        bool firstRowHasZero = false;
        for (int j = 0; j < n; ++j)
        {
            if (matrix[0][j] == 0)
            {
                firstRowHasZero = true;
                break;
            }
        }

        bool firstColHasZero = false;
        for (int i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                firstColHasZero = true;
                break;
            }
        }

        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                for (int j = 1; j < n; ++j)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        for (int j = 1; j < n; ++j)
        {
            if (matrix[0][j] == 0)
            {
                for (int i = 1; i < m; ++i)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        if (firstRowHasZero)
        {
            for (int j = 0; j < n; ++j)
            {
                matrix[0][j] = 0;
            }
        }

        if (firstColHasZero)
        {
            for (int i = 0; i < m; ++i)
            {
                matrix[i][0] = 0;
            }
        }
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
