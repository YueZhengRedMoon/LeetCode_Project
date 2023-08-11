#include <iostream>
#include <vector>

class Solution
{
public:
    int diagonalSum(std::vector<std::vector<int>> &mat)
    {
        int n = mat.size();
        int sum = 0;
        for (int i = 0, j = n - 1; i < n; ++i, --j)
        {
            sum += mat[i][i];
            if (i != j)
            {
                sum += mat[i][j];
            }
        }
        return sum;
    }
};

int main()
{
    std::cout << "For Kirie!" << std::endl;
    return 0;
}
